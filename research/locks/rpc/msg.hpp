#ifndef _MSG_HPP_
#define _MSG_HPP_

/**
 * 用于转换数据类型
 */
union cast_data_type {
    char buff[4];
    int data;
};

// 将buff中的数据转换成int
int get_int_data(char* buff);

/**
 * 消息结构
 */
struct msg_t {
    char type;
    int len;
    char* data;
};

/**
 * 提供出来消息的工具方法
 */
class msg_util_t
{
public:
	// 创建和销毁消息结构
	static msg_t* create_msg();
	static void destroy_msg(msg_t* msg);

	// 将消息编码成字节序列
	static char* encord(msg_t* msg, int& size);

	// 从fd中读取一个消息
	static void read_msg(int fd, msg_t* msg);

	// 从buff中读取一个消息
	static char* read_msg(char* buff, msg_t* msg);

	// 打印消息
	static void dump_msg(msg_t* msg);
};

#endif
