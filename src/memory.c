/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:59:13 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/22 18:51:06 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int malloc_structs(t_cmd **cmd)
{
	*cmd = NULL;

	*cmd = malloc(sizeof(t_cmd));

	ft_memset(*cmd, 0, sizeof(t_cmd));
	return (0);
}

void free_structs(t_cmd *cmd)
{
	if(cmd->path_split)
		ft_freetab(cmd->path_split);
	//if(cmd->path_command)
    //    ft_freetab(cmd->path_command);//LEAK
	//if(cmd->env)
	//	ft_freetab(cmd->env);
	if(cmd)
		free(cmd);
}
/*
void free_structs(t_cmd *cmd)
{
    if (cmd)
    {
        if (cmd->path_split)
        {
            ft_freetab(cmd->path_split);  // Free path_split array safely
            cmd->path_split = NULL;  // Set to NULL to prevent double free
        }

        // You might want to free other dynamically allocated fields here
        // if(cmd->path_command)
        //    ft_freetab(cmd->path_command);
        // if(cmd->env)
        //    ft_freetab(cmd->env);

        free(cmd);  // Finally free the main cmd structure
        cmd = NULL;
    }
}*/

static int	env_count(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

static int env_lines_copy(char **envp, int count, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < count)
	{
		cmd->env[i] = strdup(envp[i]);
		if (!cmd->env[i])
		{
			printf("malloc issues at memory.c (line 76)\n");
			while (i > 0)
			{
				free(cmd->env[i - 1]);
				i--;
			}
			free(cmd->env);
			return (EXIT_FAILURE);
		}
		i++;
	}
	cmd->env[i] = NULL;
	return (EXIT_SUCCESS);
}

int ft_copy_envp(char **envp, t_cmd *cmd)
{
	// int i;
	int count;

	// i = 0;
	count = env_count(envp);
	cmd->env = malloc(sizeof(char*) * (count + 1));
	if (!cmd->env)
		return (EXIT_FAILURE);
	if (env_lines_copy(envp, count, cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}