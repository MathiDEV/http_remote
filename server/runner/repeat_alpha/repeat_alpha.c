#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

void repeat_alpha(char *str)
{
    int i = -1;
    int j = -1;

    while (str[++i]) {
        j = -1;
        if (str[i] >= 'a' && str[i] <= 'z') {
            while (++j < str[i] - 'a' + 1)
                my_putchar(str[i]);
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            while (++j < str[i] - 'A' + 1)
                my_putchar(str[i]);
        } else
            my_putchar(str[i]);
    }
    my_putchar('\n');
}
