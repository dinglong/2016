#include "service.hpp"
#include "base_func.hpp"

int base_func_t::regist()
{
    if (service == NULL) {
        return -1;
    }
    return service->regist_func(get_name(), this);
}
