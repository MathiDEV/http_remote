#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

void rot_42(char *str)
{
    char *s = "abcdefghijklmnopqrstuvwxyz";
    char tmp;
    int i = -1;

    while (str[++i]) {
        tmp = str[i];
        if (tmp >= 'a' && tmp <= 'z') {
            tmp += 42;
            tmp -= 'a';
            my_putchar(s[(int)tmp % 26]);
        } else if (tmp >= 'A' && tmp <= 'Z') {
            tmp += 42;
            tmp -= 'A';
            my_putchar(s[(int)tmp % 26] - 32);
        } else
            my_putchar(tmp);
    }
}
