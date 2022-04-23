#include <stdio.h>
#include <unistd.h>

void rot_42(char *str);

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
    my_putstr_FORTESTING("$[All alphabet]%");
    rot_42("abcdefghijklmnopqrstuvwxyz");

    my_putstr_FORTESTING("$[Numbers and specials]%");
    rot_42("for pony 754 48 /");

    my_putstr_FORTESTING("$[Hard test]%");
    rot_42("ROT1 HORRIBLE EXERCICE Eqsdsd778788azdza0000XAMSHELL VANOURI "
           "FU\\_L KO DESSUS MDDRR HAHAHAH");

    my_putstr_FORTESTING("$\n[Empty]%");
    rot_42("");

    my_putstr_FORTESTING("$[Nothing to rotate]%");
    rot_42("42");

    my_putstr_FORTESTING("$[All and tricky]%");
    rot_42("abcdefgh45Aijklmn788==KKlooasd;=opqrstuvwxyzZ");
    return 0;
}
