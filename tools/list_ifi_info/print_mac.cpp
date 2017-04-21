/*******************************************
 * 根据指定的接口名，输出 mac 地址
 * 2012-12-23
 * dinglong
 ******************************************/
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("usage: %s <eth0|...>\n", argv[0]);
        return 1;
    }

    struct ifreq s;
    int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

    strcpy(s.ifr_name, argv[1]);
    if (0 == ioctl(fd, SIOCGIFHWADDR, &s)) {
        int i;
        for (i = 0; i < 6; ++i)
            printf(" %02x", (unsigned char) s.ifr_addr.sa_data[i]);
        puts("\n");
        return 0;
    }
    return 1;
}

