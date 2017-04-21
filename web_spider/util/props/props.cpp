#include <iostream>
#include "props.h"

const char Props::COMMENT = '#';
const std::string Props::SPACE = " \t";

Props::Props()
{
    m_props = new PropType();
}

Props::~Props()
{
    // 逐一释放存储的属性值
    PropType::iterator iter = m_props->begin();
    for (; iter != m_props->end(); iter++) {
        delete iter->first;
        delete iter->second;
    }
    m_props->clear();

    delete m_props;
}

/**
 * 从指定的文件load props
 */
void Props::load(const char* file_name)
{
    std::ifstream is(file_name);

    load(is);
    is.close();
}

void Props::load(const std::string* file_name)
{
    load(file_name->c_str());
}


/**
 * 从指定的文件流中load props
 */
void Props::load(std::ifstream& file_stream)
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
void Props::set_prop(std::string* key, std::string* value)
{
    trim(*key);
    trim(*value);

    if (key->length() > 0 && value->length() > 0) {
        if (m_props->find(key) != m_props->end()) {
            m_props->erase(key);
        }
        m_props->insert(PropTypeValue(new std::string(*key), new std::string(*value)));
    }
}

void Props::set_prop(char* key, char* value)
{
    set_prop(new std::string(key), new std::string(value));
}

/**
 * 根据key，返回指定的value
 */
std::string* Props::get_prop(const std::string* key)
{
    if (key != NULL) {
        std::string temp_key = *key;
        trim(temp_key);

        PropType::iterator iter = m_props->find(&temp_key);
        if (iter != m_props->end()) {
            return iter->second;
        }
    }

    return NULL;
}

std::string* Props::get_prop(const char* key)
{
    std::string temp_key(key);
    return get_prop(&temp_key);
}
/**
 * 打印props到标准输出
 */
void Props::list_props()
{
    PropType::iterator iter = m_props->begin();
    for (; iter != m_props->end(); iter++) {
        std::cout << *(iter->first) << '=' << *(iter->second) << std::endl;
    }
}

/**
 * 打印props到指定的文件
 */
void Props::list_props(const char* file_name)
{
    // TODO
}

void Props::list_props(const std::string* file_name)
{
    list_props(file_name->c_str());
}

/**
 * 去除string两端的空白
 */
void Props::trim(std::string& str)
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

