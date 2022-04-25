#include <stdio.h>
#include <unistd.h>

int is_in_str(char *str, char to_find)
{
    int i = -1;

    while (str[++i])
        if (str[i] == to_find)
            return (1);
    return (0);
}

int hidentf(char *s1, char *s2)
{
    int i = -1;
    int j = 0;

    while (s2[++i]) {
        if (is_in_str(s1, s2[i]))
            j++;
        if (!s1[j])
            return 1;
    }
    return (0);
}
