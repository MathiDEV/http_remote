#include <unistd.h>

void my_name(void)
{
    write(1, "Hello, World!\n", 14);
}