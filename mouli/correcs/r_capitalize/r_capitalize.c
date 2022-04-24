#include <unistd.h>

void my_putstr(char *str)
{
    int i;

    i = -1;
    while (str[++i])
        write(1, &str[i], 1);
}

void my_strcapitalize(char *str)
{
    int i = 0;

    if (str[i] >= 'a' && 'z' >= str[i])
        str[i] -= 32;
    while (str[++i]) {
        if (str[i] >= 'A' && 'Z' >= str[i])
            str[i] += 32;
        if ((str[i] >= 'a' && 'z' >= str[i]) &&
        (str[i - 1] == ' ' || str[i - 1] == '\t'))
            str[i] -= 32;
    }
    my_putstr(str);
}

void my_r_strcapitalize(char *str)
{
    int i = -1;

    while (str[++i]) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
        if ((str[i] >= 'a' && str[i] <= 'z') &&
        (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0'))
            str[i] -= 32;
    }
    my_putstr(str);
}

void r_capitalize(char *str, int order)
{
    if (order == 0)
        my_strcapitalize(str);
    else if (order == 1)
        my_r_strcapitalize(str);
    else
        write(1, "\n", 1);
}
