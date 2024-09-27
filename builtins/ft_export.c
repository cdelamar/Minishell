/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:29:31 by cdelamar          #+#    #+#             */
/*   Updated: 2024/09/05 23:48:52 by cdelamar         ###   ########.fr       */
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

    // printf("autochtone numerique\n");
    if (!name_end || !is_valid_var_name(var))
    {
        // printf ("return line 43\n");
        return (EXIT_FAILURE);
    }
    while (env[i])
    {
        // printf("J'ENVOIE LA FUMAIRE [%d] [%s]\n", i, env[i]);
        if (ft_strncmp(env[i], var, name_end - var) == 0 && env[i][name_end - var] == '=')
        {
            //printf("freeeebird [%d] [%s]\n", i, env[i]);
            //free(env[i]);
            env[i] = ft_strdup(var);
            return (EXIT_SUCCESS);
        }
        i++;
    }
    // printf("FINIS --- %s\n", env[i]);
    env[i] = ft_strdup(var);
    // printf("MINISHELL DRUCKER %s\n", env[i]);
    env[i + 1] = NULL;
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
    //printf("ft_export\n");
    if (!args[1])
    {
        print_env(cmd);
        return (EXIT_SUCCESS);
    }
    return (add_env_var(args[1], cmd));
}