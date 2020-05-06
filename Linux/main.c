#include <stdio.h>
int main()
{
        int status = file_is_ok("str");
        if (status == 0)
                puts("File existense");
        else
                puts("Error");
        return 0;
}