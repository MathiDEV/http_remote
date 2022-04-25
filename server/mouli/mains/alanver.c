#include <stdio.h>
#include <unistd.h>

void alanver(char *str);

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
    my_putstr_FORTESTING("$[Basic]%");
    alanver("EPITECH");
    newline();

    my_putstr_FORTESTING("$[One letter]%");
    alanver("b");
    newline();

    my_putstr_FORTESTING("$[BIG string]%");
    alanver("WEFQWEF48WE4F4QWEF8W4EF84WEF894WE8FW5EF456WE1F5W48F51W");
    newline();

    my_putstr_FORTESTING("$[Test on palindrome]%");
    alanver("radar bob kayak");
    newline();
    return 0;
}
