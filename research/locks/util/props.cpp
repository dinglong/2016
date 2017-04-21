#include <iostream>
#include "props.hpp"

const char props_t::COMMENT = '#';
const std::string props_t::SPACE = " \t";

props_t::props_t()
{
    props = new prop_type_t();
}

props_t::~props_t()
{
    // 逐一释放存储的属性值
    prop_type_t::iterator iter = props->begin();
    for (; iter != props->end(); iter++) {
        delete iter->first;
        delete iter->second;
    }
    props->clear();

    delete props;
}

/**
 * 从指定的文件load props
 */
void props_t::load(const char* file_name)
{
    std::ifstream is(file_name);

    load(is);
    is.close();
}

void props_t::load(const std::string* file_name)
{
    load(file_name->c_str());
}


/**
 * 从指定的文件流中load props
 */
void props_t::load(std::ifstream& file_stream)
{
    if (!file_stream.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file_stream, line)) {
        if (line.length() > 0 && line[0] != COMMENT) {
            size_t pos = line.find('=');
            size_t len = line.length();
            if (pos > 0 && pos < len) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1, len - pos);
                set_prop(&key, &value);
            }
        }
    }
}

/**
 * 设置指定的键值对应的value值
 */
void props_t::set_prop(std::string* key, std::string* value)
{
    trim(*key);
    trim(*value);

    if (key->length() > 0 && value->length() > 0) {
        if (props->find(key) != props->end()) {
            props->erase(key);
        }
        props->insert(prop_type_value_t(new std::string(*key), new std::string(*value)));
    }
}

void props_t::set_prop(char* key, char* value)
{
    set_prop(new std::string(key), new std::string(value));
}

/**
 * 根据key，返回指定的value
 */
std::string* props_t::get_prop(const std::string* key)
{
    if (key != NULL) {
        std::string temp_key = *key;
        trim(temp_key);

        prop_type_t::iterator iter = props->find(&temp_key);
        if (iter != props->end()) {
            return iter->second;
        }
    }

    return NULL;
}

std::string* props_t::get_prop(const char* key)
{
    std::string temp_key(key);
    return get_prop(&temp_key);
}
/**
 * 打印props到标准输出
 */
void props_t::list_props()
{
    prop_type_t::iterator iter = props->begin();
    for (; iter != props->end(); iter++) {
        std::cout << *(iter->first) << '=' << *(iter->second) << std::endl;
    }
}

/**
 * 打印props到指定的文件
 */
void props_t::list_props(const char* file_name)
{
    // TODO
}

void props_t::list_props(const std::string* file_name)
{
    list_props(file_name->c_str());
}

/**
 * 去除string两端的空白
 */
void props_t::trim(std::string& str)
{
    size_t pos = str.find_first_not_of(SPACE);
    if (pos >= 0) {
        str.erase(0, pos);
    } else {
        // 全部是空白字符
        str = "";
    }

    pos = str.find_last_not_of(SPACE);
    if (pos >= 0 && pos < str.length()) {
        str.erase(pos + 1, str.length() - pos);
    }
}
