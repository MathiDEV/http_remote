
#include <stdio.h>
#include <unistd.h>

void fprime(int nb);

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

int main(int argc, char *argv[])
{
    my_putstr_FORTESTING("$[Subject test]%");
    fprime(2225);

    my_putstr_FORTESTING("$\n[Small number]%");
    fprime(45);

    my_putstr_FORTESTING("$[Small number 2]%");
    fprime(98);

    my_putstr_FORTESTING("$\n[Big number]%");
    fprime(456789);

    my_putstr_FORTESTING("$[Big number 2]%");
    fprime(11111111);

    my_putstr_FORTESTING("$\n[Huge number]%");
    fprime(5448458);

    my_putstr_FORTESTING("$[Huge number 2]%");
    fprime(9807321);

    my_putstr_FORTESTING("$\n[Tricky 1]%");
    fprime(2);

    my_putstr_FORTESTING("$[Tricky 2]%");
    fprime(1);

    my_putstr_FORTESTING("$\n[Zero]%");
    fprime(0);

    my_putstr_FORTESTING("$[Negative value]%");
    fprime(-8);
    return 0;
}
