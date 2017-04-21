#include <cstdio>
#include "base_data.h"
#include "util.h"

int main()
{
    // ------------------------ int data ----------------------
    {
        Data<int> int_data;
        int_data.load("datas/int_data", get_int);

        int* ints = int_data.get_data();
        int size = int_data.get_size();

        for (int i = 1; i <= size; i++) {
            printf("data [%d] is [%d]\n", i, ints[i]);
        }

        int_data.release(NULL);
    }

    // ------------------------ char data ----------------------
    {
        Data<char> char_data;
        char_data.load("datas/char_data", get_char);

        char* chars = char_data.get_data();
        int size = char_data.get_size();
        for (int i = 1; i <= size; i++) {
            printf("data [%d] is [%c]\n", i, chars[i]);
        }

        char_data.release(NULL);
    }

    // ------------------------ string data --------------------
    {
        Data<char*> string_data;
        string_data.load("datas/string_data", get_string);

        char** strings = string_data.get_data();
        int size = string_data.get_size();

        for (int i = 1; i <= size; i++) {
            printf("data [%d] is [%s]\n", i, strings[i]);
        }

        string_data.release(release_string);
    }

    return 0;
}

