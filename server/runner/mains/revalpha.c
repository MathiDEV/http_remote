#include <stdio.h>
#include <unistd.h>

void revalpha(void);

void my_putstr_FORTESTING(char *s)
{
    int i = -1;

    while (s[++i])
        write(1, &s[i], 1);
}

int main(int argc, char *argv[])
{
    my_putstr_FORTESTING("$[Basic]%");
    revalpha();
    return 0;
}
