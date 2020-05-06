#include <stdio.h>
#include <unistd.h>
int file_is_ok(const char *name)
{
        return access(name, F_OK);
}