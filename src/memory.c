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

int malloc_structs(t_cmd **cmd, t_ctx **ctx, t_token **token)
{
	*cmd = NULL;
	*ctx = NULL;
	*token = NULL;

	*cmd = malloc(sizeof(t_cmd));
	if (!*cmd)
		return (1);
	*ctx = malloc(sizeof(t_ctx));
	if (!*ctx)
	{
		free(*cmd);
		return (1);
	}

	*token = malloc(sizeof(t_token));
	if (!*token)
	{
		free(*cmd);
		free(*ctx);
		return (1);
	}

	ft_memset(*cmd, 0, sizeof(t_cmd));
    ft_memset(*ctx, 0, sizeof(t_ctx));
    (*token)->type = WORD;  // Example initialization for t_token
    (*token)->value = NULL;
    (*token)->next = NULL;
	return (0);
}

void free_structs(t_cmd *cmd, t_ctx *ctx, t_token *token)
{
	if(cmd->path_split)
		ft_freetab(cmd->path_split);
	if(cmd)
		free(cmd);
	if(ctx)
		free(ctx);
	if(token)
		free(token);
}
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