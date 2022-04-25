#include <stdio.h>

int pgcd(int nb1, int nb2)
{
    if (nb1 <= 0 || nb2 <= 0) {
        return -1;
    }
    while (nb1 != nb2) {
        if (nb1 > nb2)
            nb1 -= nb2;
        else
            nb2 -= nb1;
    }
    return (nb1);
}