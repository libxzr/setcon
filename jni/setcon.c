#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <selinux/selinux.h>

static void help()
{
    printf("setcon by LibXZR <i@xzr.moe>\n");
    printf("Run command with specific selinux context\n");
    printf("Usage:\n");
    printf(" setcon <context> <command>\n");
    printf("Example:\n");
    printf(" setcon u:r:untrusted_app:s0 sh\n");
}

int main(int argc, char **argv)
{
    char *context;
    char **exec_args;

    // Skip filename
    argc--;
    argv++;

    if (argc == 0 || !strcmp("--help", *argv)) {
        help();
        return 0;
    }

    // Assign target context
    context = *argv;
    argc--;
    argv++;

    if (argc == 0) {
        printf("Missing command. See --help for usage\n");
        return 1;
    }

    // Forword command
    exec_args = malloc((argc + 1) * sizeof(char *));
    memcpy(exec_args, argv, argc * sizeof(char *));
    exec_args[argc] = NULL;

    // Switch context
    if (setcon(context)) {
        printf("Unable to switch to context %s\n", context);
        goto fail_clean;
    }

    // Go
    execvp(exec_args[0], exec_args);
    printf("Failed to execute command\n");

fail_clean:
    free(exec_args);
    return 1;
}
