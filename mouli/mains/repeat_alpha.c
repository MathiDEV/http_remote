#include <stdio.h>
#include <unistd.h>

void repeat_alpha(char *str);

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
    repeat_alpha("abc");

    my_putstr_FORTESTING("$[All alphabet]%");
    repeat_alpha("abcdefghijklmnopqrstuvwxyz");

    my_putstr_FORTESTING("$[Numbers and specials]%");
    repeat_alpha("for pony 754 48 /");

    my_putstr_FORTESTING("$\n[Empty]%");
    repeat_alpha("");

    my_putstr_FORTESTING("$[Tricky test]%");
    repeat_alpha("abcdefgh45Aijklmn788==KKlooasd;=opqrstuvwxyzZ");
    return 0;
}
