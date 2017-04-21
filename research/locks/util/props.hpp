#ifndef _PROPS_HPP_
#define _PROPS_HPP_

#include <fstream>
#include <string>
#include <map>
#include <assert.h>

/**
 * 比较两个 key 是否有相等的值
 */
class comp_key_t
{
public:
    bool operator()(std::string* x, std::string* y) {
        assert(x != NULL && y != NULL);

        // std::cout << "compare [" << *x << "]-[" << *y << "]." << std::endl;
        return (x->compare(*y) < 0);
    }
};

/**
 * 存储props
 */
class props_t
{
public:
    props_t();
    ~props_t();

    void load(const char* file_name);
    void load(const std::string* file_name);
    void load(std::ifstream& file_stream);

    void set_prop(char* key, char* value);
    void set_prop(std::string* key, std::string* value);

    std::string* get_prop(const char* key);
    std::string* get_prop(const std::string* key);

    void list_props();
    void list_props(const char* file_name);
    void list_props(const std::string* file_name);

private:
    void trim(std::string& str);

private:
    static const char COMMENT;
    static const std::string SPACE;

private:
    typedef std::pair<std::string*, std::string*> prop_type_value_t;
    typedef std::map<std::string*, std::string*, comp_key_t> prop_type_t;

    prop_type_t* props;
};

#endif
