#ifndef _REPLY_H_
#define _REPLY_H_

#define MAX_BUFF 819200

class Reply
{
public:
    Reply();
    ~Reply();
    char* read(int fd);

private:
    char* m_buff;
};

#endif

