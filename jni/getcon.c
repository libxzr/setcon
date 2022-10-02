#include <stdio.h>
#include <selinux/selinux.h>

int main()
{
    char *result;
    if (getcon(&result)) {
        printf("Unable to get selinux context\n");
        return 1;
    }
    printf("%s\n", result);
    freecon(result);
    return 0;
}
