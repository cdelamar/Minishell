/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:29:31 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/16 17:26:23 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int is_valid_identifier(const char *name) {
    if (!name || !*name || !(ft_isalpha(*name) || *name == '_'))
        return 0;
    while (*name) {
        if (!(ft_isalnum(*name) || *name == '_'))
            return 0;
        name++;
    }
    return 1;
}

// Function to update or add the environment variable
static int update_env(char *var, t_cmd *cmd) {
    int i = 0;
    char *name = ft_strdup(var);
    char *value = ft_strchr(name, '=');

    if (value) {
        *value = '\0';
        value++;
    }

    while (cmd->env[i]) {
        if (ft_strncmp(cmd->env[i], name, ft_strlen(name)) == 0 && cmd->env[i][ft_strlen(name)] == '=') {
            free(cmd->env[i]);
            cmd->env[i] = ft_strdup(var);
            free(name);
            return (0);
        }
        i++;
    }

    char **new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env) {
        free(name);
        return (-1);
    }

    i = 0;
    while (cmd->env[i]) {
        new_env[i] = cmd->env[i];
        i++;
    }

    new_env[i] = ft_strdup(var);
    new_env[i + 1] = NULL;
    free(cmd->env);
    cmd->env = new_env;
    free(name);
    return (0);
}

int ft_export(char **split_line, t_cmd *cmd) {
    int i = 1;

    if (!split_line[i])
	{
        // If no arguments, print the environment variables
        int j = 0;
        while (cmd->env[j]) {
            printf("declare -x %s\n", cmd->env[j]);
            j++;
        }
        return (0);
    }

    while (split_line[i])
	{
        if (is_valid_identifier(split_line[i]))
		{
            if (update_env(split_line[i], cmd) < 0)
                return (1); // Memory allocation error
        }
		else
            printf("export: `%s': not a valid identifier\n", split_line[i]);
        i++;
    }
    return (0);
}

/*
static char **realloc_env(char **env, int new_size)
{
    char **new_env;
    int i = 0;

    new_env = (char **)malloc(sizeof(char *) * (new_size + 1));
    if (!new_env)
    {
        printf("Error: malloc failed in realloc_env\n");
        return NULL;
    }

    // Copy existing entries
    while (env[i] && i < new_size)
    {
        new_env[i] = strdup(env[i]);  // Check if env[i] is not NULL before strdup
        if (!new_env[i])
        {
            printf("Error: strdup failed in realloc_env\n");
            // Clean up allocated memory
			while (i > 0)
            {
                free(new_env[--i]);
            }
            free(new_env);
            return NULL;
        }
        i++;
    }

    new_env[new_size] = NULL;

    // Free the original env if it was allocated
    //if (cmd->env)
    	//free(env);

    return new_env;
}



static int update_env(char ***env, char *name, char *value)
{
    int i = 0;
    int name_len = strlen(name);
    char *new_entry = malloc(name_len + strlen(value) + 2);

    if (!new_entry)
    {
        perror("malloc");
        return (1);
    }
    sprintf(new_entry, "%s=%s", name, value);

    // Print current environment before modification
    printf("Before update_env:\n");
    print_env(*env);

    while ((*env)[i])
    {
        if (strncmp((*env)[i], name, name_len) == 0 && (*env)[i][name_len] == '=')
        {
            free((*env)[i]);
            (*env)[i] = new_entry;

            // Print modified environment
            printf("After update_env (modified):\n");
            print_env(*env);

            return (0);
        }
        i++;
    }

    // If no existing entry was found, realloc and add new entry
    *env = realloc_env(*env, i + 1);
    if (!(*env))
    {
        free(new_entry);
        return (1);
    }
    (*env)[i] = new_entry;

    // Print updated environment after addition
    printf("After update_env (added):\n");
    print_env(*env);

    return (0);
}


int ft_export(char **args, t_cmd *cmd)
{
    int i = 1;
    char *equal_sign;

    if (!args[1])
    {
	    printf("ft_export.c (line 86)\n");
        print_env(cmd->env);
        return (0);
    }
    while (args[i])
    {
	printf("ft_export.c (line 92)\n");
        equal_sign = strchr(args[i], '=');
        if (equal_sign)
        {
		printf("ft_export.c (line 96)\n");
		*equal_sign = '\0';
            if (is_valid_identifier(args[i]))
            {
                if (update_env(&cmd->env, args[i], equal_sign + 1) != 0)
                {
			        printf("ft_export.c (line 102)\n");
		    	    return (1);
                }
            }
            else
            {
                printf("export: %s: not a valid identifier\n", args[i]);
            }
        }
        else
        {
            if (!is_valid_identifier(args[i]))
            {
                printf("export: %s: not a valid identifier\n", args[i]);
            }
        }
       	printf("ft_export.c (line 118)\n");
        i++;
    }
    return (0);
}*/