#ifndef _BASE_DATA_H_
#define _BASE_DATA_H_

#include <assert.h>
#include <cstring>

template <class DATA_T>
class Data
{
public:
    Data();
    ~Data();

    void load(const char* data_file, DATA_T(*get_data)(char*));
    void release(void (*release_data)(DATA_T));

    DATA_T* get_data() {
        return m_data;
    }

    int get_size() {
        return m_data_size;
    }

private:
    void put_data(DATA_T data);

private:
    DATA_T* m_data;
    int m_data_size;
    int m_buff_size;
};

template <class DATA_T>
Data<DATA_T>::Data()
{
    m_data = new DATA_T[32];
    m_buff_size = 32;
    m_data_size = 0;
}

template <class DATA_T>
Data<DATA_T>::~Data()
{
    delete []m_data;
}

template <class DATA_T>
void Data<DATA_T>::load(const char* data_file, DATA_T(*get_data)(char*))
{
    // TODO 假设每一个token的长度不会超过 256
    char buff[256];

    FILE* pf = fopen(data_file, "r");
    if (pf == NULL) {
        perror("open file error");
        return;
    }

    int index = 0;
    while (true) {
        int data = getc(pf);
        char ch = (char)data;

        if (data != EOF && ch != '\t' && ch != '\n' && ch != '\r' && ch != ' ') {
            buff[index++] = ch;
        } else if (index > 0) {
            buff[index] = '\0';
            DATA_T data = get_data(buff);
            put_data(data);
            index = 0;
        }

        if (data == EOF) {
            break;
        }

        assert(index < 256);
    }

    fclose(pf);
}

template <class DATA_T>
void Data<DATA_T>::release(void (*release_data)(DATA_T))
{
    if (release_data != NULL) {
        for (int i = 1; i < m_data_size; i++) {
            release_data(m_data[i]);
        }
    }
}

template <class DATA_T>
void Data<DATA_T>::put_data(DATA_T data)
{
    // 长度超过buff限制，resize
    if (m_data_size > m_buff_size) {
        DATA_T* tmp = m_data;
        m_data = new DATA_T[2 * m_buff_size];
        memcpy(m_data, tmp, m_data_size + 1);
        delete []tmp;
    }

    // 从 1 开始放置数据
    m_data[++m_data_size] = data;
}

#endif

