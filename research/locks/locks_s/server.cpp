#include <cstdio>
#include "base_func.hpp"
#include "service.hpp"
#include "msg.hpp"

// ----------------------------------------------
// 做测试使用
// ----------------------------------------------
class test_func_t : public base_func_t
{
public:
    test_func_t(service_t* s) : base_func_t(s) {}

    int invoke(char* params) {
        printf("xxxxxx here xxxxxx\n");

		// 第一个参数
		msg_t* msg_1 = msg_util_t::create_msg();
		params = msg_util_t::read_msg(params, msg_1);
		
		// 第二个参数
		msg_t* msg_2 = msg_util_t::create_msg();
		params = msg_util_t::read_msg(params, msg_2);

		int param_1;
		char* param_2;
		memcpy(&param_1, msg_1->data, sizeof(int));
		param_2 = msg_2->data;

		// 调用实际的服务函数
		hello(param_1, param_2);

		msg_util_t::destroy_msg(msg_1);
		msg_util_t::destroy_msg(msg_2);

        return 0;
    }

    char* get_name() {
        return "test_func_t";
    }

private:
	void hello(int id, char* msg) {
		printf("%d say: [%s].\n", id, msg);
	}
};


// **********************************************
// main
// **********************************************
int main(int argc, char* argv[])
{
    service_t* s = new service_t();

    // 注册框架服务类
    test_func_t* tf = new test_func_t(s);
    tf->regist();

    // 初始化并启动服务
    s->init(6700);
    s->run();

    return 0;
}
