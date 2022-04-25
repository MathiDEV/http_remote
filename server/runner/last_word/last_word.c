#include <unistd.h>
void last_word(char *str)
{
    int j;
    int i;

    i = 0;
    j = 0;
    while (str[i]) {
        if (str[i] == ' ' && str[i + 1] >= 33 && str[i + 1] <= 126)
            j = i + 1;
        i++;
    }
    while (str[j] >= 33 && str[j] <= 127) {
        write(1, &str[j], 1);
        j++;
    }
    write(1, "\n", 1);
}
