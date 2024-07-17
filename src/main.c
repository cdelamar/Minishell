/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:06:47 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/17 18:06:50 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *line;
	t_cmd *cmd;
	t_ctx *ctx;
	t_token *token;

	(void)argc;
	(void)argv;

	// CTRL + C and CTRL + '\'
	signals();

	// SHELL LOOP
	while (1)
	{
		if (malloc_structs(&cmd, &ctx, &token) != 0)
		{
			ft_putendl_fd(MALLOC_FAILURE, 2);
			return (1);
		}
		cmd->env = envp;
		/*if (ft_copy_envp(envp, cmd) == 1)
			return (EXIT_FAILURE);*/
		line = readline("MINISHELL>");

		// CTRL + D
		if (line == NULL)
		{
			free_structs(cmd, ctx, token);
			printf("CTRL + D\n");
			return (0);
		}

		// HISTORY LINE
		if (*line)
			add_history(line);

		// EXECUTING
		if (execute(line, cmd) == EXIT_COMMAND) // define OK ?
		{
			// modif de var_g
			free_structs(cmd, ctx, token);
			free(line);
			return (0);
		}
		free_structs(cmd, ctx, token);
		free(line);
	}
	// free_structs(cmd, ctx, token);
	// free(line);
	return (0);
}

