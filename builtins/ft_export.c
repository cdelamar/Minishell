/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:29:31 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/23 11:50:11 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



// Function to check if a variable name is valid
int is_valid_var_name(char *name)
{
    int i;

    i = 0;
    if (!ft_isalpha(name[0]) && name[0] != '_')
        return (0);
    while (name[i] && name[i] != '=')
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

// Function to add or update an environment variable
int add_env_var(char *var, t_cmd *cmd)
{
    int i = 0;
    char **env = cmd->env;
    char *name_end = ft_strchr(var, '=');

    if (!name_end || !is_valid_var_name(var))
    {
        printf ("return line 43\n");
        return (1);
    }
    while (env[i])
    {
        if (ft_strncmp(env[i], var, name_end - var) == 0 && env[i][name_end - var] == '=')
        {
            printf("\n\n\nca libere ici (line 48)\n\n\n");
            free(env[i]);
            env[i] = ft_strdup(var);
            return (0);
        }
        i++;
    }
    env[i] = ft_strdup(var);
    env[i + 1] = NULL;
    printf("return (line 57)\n");
    printf("\n\nenv n %d : '%s'\n\n", i, env[i]);
    return (0);
}

void print_env(t_cmd *cmd)
{
    int i = 0;
    while (cmd->env[i])
    {
        printf("%s\n", cmd->env[i]);
        i++;
    }
}

int ft_export(char **args, t_cmd *cmd)
{
    printf ("je passe bien dans mon builtin 'export'\n");
    if (!args[1])
    {
        //print_env(cmd);
        printf("print_env\n");
        return (EXIT_SUCCESS);
    }
    printf("return (line 79)\n");
    return (add_env_var(args[1], cmd));
}