#include "../includes/minishell.h"

void print_env(t_cmd *cmd)
{
    int i = 0;

    while (cmd->env[i])
    {
        printf("%s\n", cmd->env[i]);
        i++;
    }
}

int ft_export(char *arg)
{
    char *equal_sign = strchr(arg, '=');
    if (equal_sign == NULL)
    {
        fprintf(stderr, "export: invalid argument\n");
        return 1;
    }
    *equal_sign = '\0';
    if (setenv(arg, equal_sign + 1, 1) != 0)
    {
        perror("setenv");
        return 1;
    }
    return 0;
}