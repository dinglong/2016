#include <unistd.h>
#include <arpa/inet.h>
#include <cstdio>
#include <errno.h>
#include <cstring>
#include <cstdlib>

void write_prefix(int cfd)
{
    int len = write(cfd, "\nts>", 4);
    if (len < 0) {
        perror("write prefix error");
    }
}

char* put_data(char* buff, char ch, int index, int buff_len)
{
    char* ret_buff = buff;

    if (index > buff_len) {
        ret_buff = new char[2 * buff_len];
        memcpy(ret_buff, buff, buff_len);
    }

    ret_buff[index] = ch;
    return ret_buff;
}

int init_sfd(int port)
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) {
        perror("create socket error");
        exit(1);
    }

    sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sfd, (sockaddr*)&saddr, sizeof(sockaddr)) < 0) {
        perror("bind socket error");
        exit(1);
    }

    if (listen(sfd, 256) < 0) {
        perror("listen socket error");
        exit(1);
    }

    return sfd;
}

int accept_req(int sfd)
{
    sockaddr_in caddr;
    socklen_t caddr_len = sizeof(sockaddr);
    int cfd = accept(sfd, (sockaddr*)&caddr, &caddr_len);
    if (cfd < 0) {
        perror("accept socket error");
        return -1;
    }

    // TODO print client addr

    write_prefix(cfd);

    return cfd;
}

void process_data(int cfd, bool (*do_f)(int cfd, const char* pdata))
{
    // 接受数据以换行结束
    static const int buff_len = 1024;
    char* buff = new char[buff_len];

    char ch;
    bool has_next = true;
    while (has_next) {

        int index = 0;
        while (true) {
            if (read(cfd, &ch, 1) < 0) {
                has_next = false;
                break;
            } else if ('\n' == ch) {
                buff = put_data(buff, '\0', index, buff_len);
                break;
            } else {
                buff = put_data(buff, ch, index, buff_len);
            }
            index++;
        }

        has_next = do_f(cfd, buff);
        write_prefix(cfd);
    }

    delete []buff;
    close(cfd);
}

bool do_f(int cfd, const char* buff)
{
    // TODO 目前是简单的回写数据
    int write_len = 0;
    int len = strlen(buff);

    printf("process data: [%d] %s\n", len, buff);

    while (write_len < len) {
        int wl = write(cfd, &buff[write_len], len - write_len);

        if (wl < 0) {
            perror("write data error");
            return false;
        }

        write_len += wl;
    }

    if (strncmp(buff, "bye", 3) == 0) {
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    int sfd = init_sfd(23222);

    printf("ts is ready...\n");

    int cfd = -1;
    while ((cfd = accept_req(sfd)) > 0) {
        process_data(cfd, do_f);
    }

    printf("ts over.\n");

    return 0;
}

