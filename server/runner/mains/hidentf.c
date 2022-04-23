#include <stdio.h>
#include <unistd.h>

int hidentf(char *s1, char *s2);

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
    int ret = 0;

    my_putstr_FORTESTING("$[Alphabet expect 1]%");
    ret = hidentf("abc", "abcdefghjikqsdblablabla");
    my_putnbr(ret);
    newline();

    my_putstr_FORTESTING("$[Random expect 1]%");
    ret = hidentf("fgex", "tyf34gdgf;'ektufjhgdgex.;.;rtjynur6");
    my_putnbr(ret);
    newline();

    my_putstr_FORTESTING("$[Wrong alphabet expect 0]%");
    ret = hidentf("azbc", "btarc");
    my_putnbr(ret);
    newline();
    return 0;
}
