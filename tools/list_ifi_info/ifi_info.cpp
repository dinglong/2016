#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if.h>
#include "ifi_info.h"

IFIList::IFIList()
{
    m_base = NULL;
}

void IFIList::read_ifi_infos()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("create socket error");
        exit(1);
    }

    struct ifconf* ifc = get_ifconf(sockfd);

    char* buff = (char*)ifc->ifc_buf; // ifconf结构中存储ifreq的部分
    for (char* ptr = buff; ptr < buff + ifc->ifc_len; ptr += sizeof(struct ifreq)) {
        struct ifreq* ifr = (struct ifreq*)ptr;

        ifi_info* pinfo = new ifi_info();
        // 填充名字
        memcpy(pinfo->ifi_name, ifr->ifr_name, strlen(ifr->ifr_name) + 1);
        printf("name - %s\n", pinfo->ifi_name);

        // 填充addr
        pinfo->ifi_addr = (struct sockaddr*)new struct sockaddr_in();
        memcpy(pinfo->ifi_addr, (struct sockaddr_in*)&ifr->ifr_addr, sizeof(struct sockaddr_in));
        printf("addr- %s\n", sock_ntop(pinfo->ifi_addr, sizeof(sockaddr_in)));

        // TODO 填充index

        // 填充flags
        Ioctl(sockfd, SIOCGIFFLAGS, ifr);
        pinfo->ifi_flags = ifr->ifr_flags;
        printf("flag - %d\n", pinfo->ifi_flags);

        // 填充mtu
        Ioctl(sockfd, SIOCGIFMTU, ifr);
        pinfo->ifi_mtu = ifr->ifr_mtu;
        printf("mtu - %d\n", pinfo->ifi_mtu);

        // 填充mac地址
        Ioctl(sockfd, SIOCGIFHWADDR, ifr);
        memcpy(pinfo->ifi_haddr, ifr->ifr_addr.sa_data, sizeof(ifr->ifr_addr.sa_data));
        printf("mac - ");
        for (int i = 0; i < 6; ++i) {
            printf("%02x ", (unsigned char) pinfo->ifi_haddr[i]);
        }
        printf("\n");

        // 多播地址
        Ioctl(sockfd, SIOCGIFBRDADDR, ifr);
        pinfo->ifi_brdaddr = (struct sockaddr*)new struct sockaddr_in();
        memcpy(pinfo->ifi_brdaddr, (struct sockaddr_in*)&ifr->ifr_broadaddr, sizeof(struct sockaddr_in));
        printf("brdaddr- %s\n", sock_ntop(pinfo->ifi_brdaddr, sizeof(sockaddr_in)));

        // TODO 点对点地址

        // TODO 增加到列表中
    }

    /*
    	#ifdef HAVE_SOCKADDR_DL_STRUCT
    	if(ifr->ifr_addr.sa_family == AF_LINK) {
    		struct sockaddr_dl* sdl = (struct sockaddr_dl*)&ifr->ifr_addr;
    		char* sdlname = ifr->ifr_name;
    		int idx = sdl->sdl_index;
    		haddr = sdl->sdl_data + sdl->sdl_nlen;
    		hlen = sdl->sdl_alen;
    	}
    	#endif
    */
}

void IFIList::dump_ifi_infos()
{

}

ifi_info* IFIList::get_ifi_info(const char* name)
{

}

IFIList::~IFIList()
{
    while (m_base != NULL) {
        ifi_info* ptr = m_base;
        m_base = m_base->next;
        delete ptr;

    }

    m_base = NULL;
}

struct ifconf* IFIList::get_ifconf(int sockfd) {
    struct ifconf* ifc = new struct ifconf();

    int lastlen = 0;
    int len = 128 * sizeof(struct ifreq);
    while (true) {
        char* buff = new char[len];

        ifc->ifc_len = len;
        ifc->ifc_buf = buff;

        if (ioctl(sockfd, SIOCGIFCONF, ifc) < 0) {
            if (errno != EINVAL || lastlen != 0) {
                perror("ioctl error");
                exit(1);
            }
        } else {
            if (ifc->ifc_len == lastlen) {
                break;
            }
            lastlen = ifc->ifc_len;
        }

        // 重新分配空间
        len += 16 * sizeof(struct ifreq);
        delete []buff;
    }

    return ifc;
}

int IFIList::Ioctl(int fd, int flag, void* ref)
{
    int ret = ioctl(fd, flag, ref);
    if (ret < 0) {
        perror("ioctl error");
        exit(0);
    }
    return ret;
}

char* IFIList::sock_ntop(const struct sockaddr* sa, socklen_t salen)
{
    char portstr[8];
    static char str[128];

    switch (sa->sa_family) {
    case AF_INET: {
        struct sockaddr_in* sin = (struct sockaddr_in*)sa;
        if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL) {
            return NULL;
        }
        if (ntohs(sin->sin_port) != 0) {
            snprintf(portstr, sizeof(portstr), ":%d", ntohs(sin->sin_port));
            strcat(str, portstr);
        }
        return str;
    }
    default:
        printf("other family.\n");
    }
}

int main()
{
    IFIList ifl;
    ifl.read_ifi_infos();
}

