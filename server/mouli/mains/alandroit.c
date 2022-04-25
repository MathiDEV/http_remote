#include <stdio.h>
#include <unistd.h>

void alandroit(char *str);

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
    alandroit("EPITECH");
    newline();

    my_putstr_FORTESTING("$[One letter]%");
    alandroit("b");
    newline();

    my_putstr_FORTESTING("$[Big string]%");
    alandroit("WEFQWEF48WE4F4QWEF8W4EF84WEF894WE8FW5EF456WE1F5W48F51W");
    newline();
    return 0;
}
