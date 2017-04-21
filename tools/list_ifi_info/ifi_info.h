#ifndef _IFI_INFO_H_
#define _IFI_INFO_H_

#define IFI_NAME 16
#define IFI_HADDR 8

typedef unsigned char u_char;
typedef unsigned short u_short;

typedef struct InfoStruct {
    char ifi_name[IFI_NAME];
    short ifi_index;
    short ifi_mtu;

    u_char ifi_haddr[IFI_HADDR]; // 硬件地址
    u_short ifi_hlen; // 硬件地址长度

    short ifi_flags;
    short ifi_myflags;

    struct sockaddr* ifi_addr;
    struct sockaddr* ifi_brdaddr;
    struct sockaddr* ifi_dstaddr;

    struct InfoStruct* next;
} ifi_info;

class IFIList
{
public:
    void read_ifi_infos();
    void dump_ifi_infos();
    ifi_info* get_ifi_info(const char* name);

    IFIList();
    ~IFIList();

private:
    struct ifconf* get_ifconf(int sockfd);
    int Ioctl(int fd, int flag, void* ref);
    char* sock_ntop(const struct sockaddr* sa, socklen_t salen);

private:
    ifi_info* m_base;
};

#endif

