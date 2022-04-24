#include <unistd.h>

int countoc(char *str, char to_find)
{
    int i = -1;
    int count = 0;

    while (str[++i])
        if (str[i] == to_find)
            count++;
    return (count);
}