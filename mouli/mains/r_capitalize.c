#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void r_capitalize(char *str, int order);

void my_putstr_FORTESTING(char *s)
{
    int i = -1;

    while (s[++i])
        write(1, &s[i], 1);
}

int my_strlen_FORTESTING(char *s)
{
    int i = 0;

    while (s[i])
        i++;
    return (i);
}

char *my_strdup_FORTESTING(char *s)
{
    char *str;
    int i = 0;

    str = malloc(sizeof(char) * (my_strlen_FORTESTING(s) + 1));
    while (s[i]) {
        str[i] = s[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

void newline(void)
{
    write(1, "\n", 1);
}

int main(int argc, char *argv[])
{
    my_putstr_FORTESTING("$[ORDER 0 | Basic]%");
    r_capitalize(my_strdup_FORTESTING("hello world uwu"), 0);

    my_putstr_FORTESTING("$[ORDER 0 | One word]%");
    r_capitalize(my_strdup_FORTESTING("hello_world_uwu"), 0);

    my_putstr_FORTESTING("$[ORDER 0 | FULL CAPS]%");
    r_capitalize(
    my_strdup_FORTESTING("POURQUOI JE CRIE AAAAAAAAAAAAAAAAA"), 0);

    my_putstr_FORTESTING("$[ORDER 0 | Big sentence and numbers]%");
    r_capitalize(my_strdup_FORTESTING("VAVARIER EST LE MEILLEUR TEK1 DE LA "
                                      "TER99RE car je l'aime tr+op trop uwu"),
    0);

    my_putstr_FORTESTING("$[ORDER 0 | Empty]%");
    r_capitalize(my_strdup_FORTESTING(""), 0);

    my_putstr_FORTESTING("$\n[ORDER 1 | Basic]%");
    r_capitalize(my_strdup_FORTESTING("hello world uwu"), 1);

    my_putstr_FORTESTING("$[ORDER 1 | One word]%");
    r_capitalize(my_strdup_FORTESTING("hello_world_uwu"), 1);

    my_putstr_FORTESTING("$[ORDER 1 | FULL CAPS]%");
    r_capitalize(
    my_strdup_FORTESTING("POURQUOI JE CRIE AAAAAAAAAAAAAAAAA"), 1);

    my_putstr_FORTESTING("$[ORDER 1 | Big sentence and numbers]%");
    r_capitalize(my_strdup_FORTESTING("VAVARIER EST LE MEILLEUR TEK1 DE LA "
                                      "TER99RE car je l'aime tr+op trop uwu"),
    1);

    my_putstr_FORTESTING("$[ORDER 1 | Empty]%");
    r_capitalize(my_strdup_FORTESTING(""), 1);

    my_putstr_FORTESTING("$\n[Error handling wrong order]%");
    r_capitalize(my_strdup_FORTESTING("saluut ;)"), 2);
    return 0;
}
