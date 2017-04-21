#include <cstdlib>
#include <cstring>
#include "msg.hpp"
#include "util.hpp"

/**
 * 将buff中的前四个自己的数据转换成int
 * TODO 不同机器的兼容（大小端，32/64位）
 */
int get_int_data(char* buff)
{
    cast_data_type cdt;

    cdt.buff[0] = buff[0];
    cdt.buff[1] = buff[1];
    cdt.buff[2] = buff[2];
    cdt.buff[3] = buff[3];

    return cdt.data;
}

/**
 * 分配一个消息结构
 */
msg_t* msg_util_t::create_msg()
{
    msg_t* msg = (msg_t*) malloc(sizeof(msg_t));
    return msg;
}

/**
 * 销毁一个消息
 */
void msg_util_t::destroy_msg(msg_t* msg)
{
    if (msg->data != 0) {
        free(msg->data);
    }

    free(msg);
}

/**
 * 从fd中读出一个msg_t
 */
void msg_util_t::read_msg(int fd, msg_t* msg)
{
	// type field
    int ret = util_t::read_n(fd, &(msg->type), sizeof(msg->type));
    util_t::assert_ret(ret);
    printf("msg type: %c\n", msg->type);

    // len field
	char buff[8];
    ret = util_t::read_n(fd, buff, sizeof(msg->len));
    util_t::assert_ret(ret);
    msg->len = get_int_data(buff);
    printf("msg len : %d\n", msg->len);

	// data field
    msg->data = (char*) malloc(msg->len + 1);
    ret = util_t::read_n(fd, msg->data, msg->len);
    util_t::assert_ret(ret);
    msg->data[msg->len] = '\0';
}

char* msg_util_t::read_msg(char* buff, msg_t* msg)
{
	// type field
	memcpy(&(msg->type), buff, sizeof(msg->type));
	buff += sizeof(msg->type);
	printf("msg type: %c\n", msg->type);

	// len field
	char tmp[8];
	memcpy(tmp, buff, sizeof(msg->len));
	msg->len = get_int_data(tmp);
	buff += sizeof(msg->len);
	printf("msg len : %d\n", msg->len);

	// data field
	msg->data = (char*) malloc(msg->len + 1);
	memcpy(msg->data, buff, msg->len);
	msg->data[msg->len] = '\0';
	buff += msg->len;
	printf("msg data: %s\n", msg->data);

	return buff;
}

/**
 * 将消息编码成marsh到一个buff中，以便于socket发送
 */
char* msg_util_t::encord(msg_t* msg, int& size)
{
    int type_size = sizeof(msg->type);
    int len_size = sizeof(msg->len);
    int data_size = msg->len;

    size = type_size + len_size + data_size;

    char* buff = (char*) malloc(size);

    memcpy(buff, &(msg->type), type_size);
    memcpy(buff + type_size, &(msg->len), len_size);
    memcpy(buff + type_size + len_size, msg->data, data_size);

    return buff;
}

void msg_util_t::dump_msg(msg_t* msg)
{
    printf("----- dump msg start -----\n");
    printf("msg type: %c\n", msg->type);
    printf("msg len : %d\n", msg->len);
    printf("msg data: %s\n", msg->data);
    printf("----- dump msg end   -----\n");
}
