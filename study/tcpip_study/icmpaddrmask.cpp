/*
 * Issue an ICMP address mask request and print the reply.
 *
 * This program originated from the public domain ping program written
 * by Mike Muuss.
 *
 * You must be superuser to run this program (or it must be suid to root)
 * since it requires a raw socket.
 */
#include <sys/param.h>
#include <sys/signal.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define	DEFDATALEN	(12)	/* default data length */
#define	MAXIPLEN	60
#define	MAXICMPLEN	76
#define	MAXPACKET	(65536 - 60 - 8)/* max packet size */

int datalen = DEFDATALEN;
int s;
u_char outpack[MAXPACKET];
char* hostname;
int response = 0;

u_short in_cksum(u_short* addr, int len);
void sender(struct sockaddr* from);
void procpack(char* buf, int cc, struct sockaddr_in* from);
void sig_alrm(int);

int main(int argc, char* argv[])
{
    struct sockaddr from;
    struct hostent* hp;
    struct sockaddr_in*	to;
    struct protoent* proto;
    u_char* packet;
    char hnamebuf[MAXHOSTNAMELEN];

    if (argc != 2) {
        printf("usage: %s <ip>\n", argv[0]);
        return 1;
    }

    bzero((char*)&from, sizeof(struct sockaddr));
    to = (struct sockaddr_in*)&from;
    to->sin_family = AF_INET;

    /*
     * try to convert as dotted decimal address,
     * else if that fails assume it's a hostname
     */
    char* target = argv[1];
    to->sin_addr.s_addr = inet_addr(target);
    if (to->sin_addr.s_addr != (u_int) - 1) {
        hostname = target;
    } else {
        hp = gethostbyname(target);
        if (!hp) {
            fprintf(stderr, "unknown host %s\n", target);
            exit(1);
        }
        to->sin_family = hp->h_addrtype;
        bcopy(hp->h_addr, (caddr_t)&to->sin_addr, hp->h_length);
        strncpy(hnamebuf, hp->h_name, sizeof(hnamebuf) - 1);
        hostname = hnamebuf;
    }

    int packlen = datalen + MAXIPLEN + MAXICMPLEN;
    if ((packet = (u_char*)malloc((u_int)packlen)) == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    if ((proto = getprotobyname("icmp")) == NULL) {
        fprintf(stderr, "unknown protocol icmp\n");
        exit(1);
    }
    if ((s = socket(AF_INET, SOCK_RAW, proto->p_proto)) < 0) {
        perror("socket");	/* probably not running as superuser */
        exit(1);
    }

	int on = 1;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR | SO_BROADCAST, &on, sizeof(on));

    /*
     * We send one request, then wait 5 seconds, printing any
     * replies that come back.  This lets us send a request to
     * a broadcast address and print multiple replies.
     */
    signal(SIGALRM, sig_alrm);
    alarm(10);	/* 5 second time limit */

    sender(&from);	/* send the request */

    for (;;) {
        struct sockaddr_in	from;
        socklen_t	 cc, fromlen;
        fromlen = sizeof(from);
        if ((cc = recvfrom(s, (char*)packet, packlen, 0, (struct sockaddr*)&from, &fromlen)) < 0) {
            if (errno == EINTR)
                continue;
            perror("recvfrom error");
            continue;
        }
        procpack((char*)packet, cc, &from);
    }
}

/*
 * Send the ICMP address mask request.
 */
void sender(struct sockaddr* from)
{
    struct icmp* icp;
    icp = (struct icmp*)outpack;
    icp->icmp_type = ICMP_MASKREQ;
    icp->icmp_code = 0;
    icp->icmp_cksum = 0;	/* compute checksum below */
    icp->icmp_seq = 12345;	/* seq and id must be reflected */
    icp->icmp_id = getpid();
    icp->icmp_mask = 0;
    int cc = ICMP_MASKLEN;	/* 12 = 8 bytes of header, 4 bytes of mask */

    /* compute ICMP checksum here */
    icp->icmp_cksum = in_cksum((u_short*)icp, cc);
    int sendlen = sendto(s, (char*)outpack, cc, 0, from, sizeof(struct sockaddr));
    if (sendlen < 0 || sendlen != cc)  {
        if (sendlen < 0) {
            perror("sendto error");
        }
        printf("wrote %s %d chars, ret=%d\n", hostname, cc, sendlen);
    }
}

/*
 * Process a received ICMP message.
 */
void procpack(char* buf, int cc, struct sockaddr_in* from)
{
    /* Check the IP header */
    struct ip* ip = (struct ip*)buf;
    int hlen = ip->ip_hl << 2;
    if (cc < hlen + ICMP_MINLEN) {
        fprintf(stderr, "packet too short (%d bytes) from %sn", cc,
                inet_ntoa(*(struct in_addr*)&from->sin_addr.s_addr));
        return;
    }

    /* Now the ICMP part */
    cc -= hlen;
    struct icmp* icp = (struct icmp*)(buf + hlen);

    /* With a raw ICMP socket we get all ICMP packets that come into the kernel. */
    if (icp->icmp_type == ICMP_MASKREPLY) {
        if (cc != ICMP_MASKLEN)
            printf("cc = %d, expected cc = 12n", cc);
        if (icp->icmp_seq != 12345)
            printf("received sequence # %dn", icp->icmp_seq);
        if (icp->icmp_id != getpid())
            printf("received id %dn", icp->icmp_id);
        printf("received mask = %08x, from %sn",
                ntohl(icp->icmp_mask),
                inet_ntoa(*(struct in_addr*) &from->sin_addr.s_addr));
        response++;
    }
    /* We ignore all other types of ICMP messages */
}

/*
 * Checksum routine for Internet Protocol family headers (C Version)
 */
u_short in_cksum(u_short* addr, int len)
{
    int nleft = len;
    u_short* w = addr;
    int sum = 0;
    u_short answer = 0;

    /*
     * Our algorithm is simple, using a 32 bit accumulator (sum), we add
     * sequential 16 bit words to it, and at the end, fold back all the
     * carry bits from the top 16 bits into the lower 16 bits.
     */
    while (nleft > 1)  {
        sum += *w++;
        nleft -= 2;
    }

    /* mop up an odd byte, if necessary */
    if (nleft == 1) {
        *(u_char*)(&answer) = *(u_char*)w;
        sum += answer;
    }

    /* add back carry outs from top 16 bits to low 16 bits */
    sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
    sum += (sum >> 16);	 /* add carry */
    answer = ~sum;	 /* truncate to 16 bits */

    return(answer);
}

void sig_alrm(int signo)
{
    if (response == 0) {
        printf("timeout\n");
        exit(1);
    }
    exit(0);	/* we got one or more responses */
}

