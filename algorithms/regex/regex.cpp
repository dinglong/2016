#include <cstdio>
#include <cstring>

int matchhere(char* regexp, char* text);
int matchstar(int c, char* regexp, char* text);

int match(char* regexp, char* text)
{
    if (regexp[0] == '^') {
        return matchhere(regexp, text);
    }

    do {
        if (matchhere(regexp, text)) {
            return 1;
        }
    } while (*text++ != '\0');

    return 0;
}

int matchhere(char* regexp, char* text)
{
    if (regexp[0] == '\0') {
        return 1;
    }
    if (regexp[1] == '*') {
        return matchstar(regexp[0], regexp + 2, text);
    }
    if (regexp[0] == '$' && regexp[1] == '\0') {
        return *text == '\0';
    }
    if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text)) {
        return matchhere(regexp + 1, text + 1);
    }

    return 0;
}

int matchstar(int c, char* regexp, char* text)
{
    do {
        if (matchhere(regexp, text)) {
            return 1;
        }
    } while (*text != '\0' && (*text++ == c || c == '.'));

    return 0;
}

int main(int argc, char* argv[])
{
    char buff[1024];
    char* pline = NULL;
    int linenum = 1;

    if (argc < 2) {
        printf("usage: %s <regex>\n", argv[0]);
        return 1;
    }

    while ((pline = fgets(buff, 1024, stdin)) != NULL) {
        pline[strlen(pline) - 1] = '\0';
        if (match(argv[1], pline)) {
            printf("%d - [%s]\n", linenum, pline);
        }
        linenum++;
    }

    return 0;
}

