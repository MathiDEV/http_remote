#include <unistd.h>

static int my_strlen(char *str)
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

void alanver(char *str)
{
    int i = my_strlen(str);

    while (str[--i])
        write(1, &str[i], 1);
}
