#include <stdio.h>
#include <unistd.h>

void last_word(char *str);

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
    my_putstr_FORTESTING("$[Simple]%");
    last_word("Hello World");

    my_putstr_FORTESTING("$[Only one word]%");
    last_word("Hello_World!");

    my_putstr_FORTESTING("$[Lots of words]%");
    last_word(
    "Hello_World! SALUT LES TEK0 JESPERE QUE CETTE JOURNEE ROULE NORMINET");

    my_putstr_FORTESTING("$[Tabs and spaces stress test]%");
    last_word("Hello\tWorld!");

    my_putstr_FORTESTING("$[Tabs and spaces stress test at the end too]%");
    last_word("Hello\tWorld! chien chat E-ARTSUP MANGER ZAZ ET VAVARIER       "
              "   \t\t\t                      5       \t\t\t\t      ");

    my_putstr_FORTESTING("$[Empty]%");
    last_word("");
    return 0;
}
