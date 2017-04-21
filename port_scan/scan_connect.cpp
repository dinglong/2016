#include <cstdio>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <signal.h>
#include <arpa/inet.h>
#include "util.h"

void connect_alarm(int signo)
{
    return;
}

int connect_timeout(int sockfd, const sockaddr* paddr, socklen_t salen, int nsec)
{
    int ret = 0;

    sigfunc* sf = signal(SIGALRM, connect_alarm);
    if (alarm(nsec) != 0) {
        perror("connect timeout: alarm was already set");
    }

    if ((ret = connect(sockfd, paddr, salen)) < 0) {
        close(sockfd);
        if (errno == EINTR) {
            errno = ETIMEDOUT;
        }
    }
    alarm(0);
    signal(SIGALRM, sf);

    return ret;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("usage: %s <host>\n", argv[0]);
        return 1;
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, argv[1], &addr.sin_addr) <= 0) {
        perror("inet_pton error\n");
        return 1;
    }

    for (int i = 80; i < 100; i++) {
        printf("connect port %d ...\n", i);

        addr.sin_port = htons(i);

        int sfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sfd < 0) {
            perror("create socket");
            return 1;
        }

        if (connect_timeout(sfd, (struct sockaddr*)&addr, sizeof(addr), 1) < 0) {
            perror("connect error");
        }

        close(sfd);
    }

    return 0;
}

