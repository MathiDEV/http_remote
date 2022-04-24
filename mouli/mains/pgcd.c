#include <stdio.h>
#include <unistd.h>

int pgcd(int nb1, int nb2);

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr_FORTESTING(char *s)
{
    int i = -1;

    while (s[++i])
        write(1, &s[i], 1);
}

void newline(void)
{
    write(1, "\n", 1);
}

void my_putnbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10) {
        my_putnbr(nb / 10);
    }
    my_putchar(nb % 10 + '0');
}

int main(int argc, char *argv[])
{
    int ret = 0;

    my_putstr_FORTESTING("$[Subject test]%");
    ret = pgcd(14, 77);
    my_putnbr(ret);
    newline();

    my_putstr_FORTESTING("$[Same numbers]%");
    ret = pgcd(5, 5);
    my_putnbr(ret);
    newline();

    my_putstr_FORTESTING("$[Medium numbers]%");
    ret = pgcd(7888, 1545);
    my_putnbr(ret);
    newline();

    my_putstr_FORTESTING("$[Huge numbers]%");
    ret = pgcd(123456, 789456);
    my_putnbr(ret);
    newline();

    my_putstr_FORTESTING("$[Division by zero]%");
    ret = pgcd(1, 0);
    my_putnbr(ret);
    newline();

    my_putstr_FORTESTING("$[Negative numbers]%");
    ret = pgcd(78, -5);
    my_putnbr(ret);
    newline();
    return 0;
}
