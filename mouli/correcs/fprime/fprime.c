#include "unistd.h"
#include <stdio.h>

void my_putchar(char c)
{
    write(1, &c, 1);
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

void fprime(int nb)
{
    int div = 2;
    int f = 0;

    if (nb <= 1) {
        my_putnbr(nb);
        return;
    }
    while (nb != 1) {
        if (nb % div == 0) {
            if (f != 0)
                write(1, "*", 1);
            my_putnbr(div);
            nb = nb / div;
            div = 2;
            f++;
        } else
            div++;
    }
    write(1, "\n", 1);
}
