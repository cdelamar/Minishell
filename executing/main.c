/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:37:07 by cdelamar          #+#    #+#             */
/*   Updated: 2024/06/14 21:54:47 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
 *							init_cmd
 *
 *	WIP : TODO
 *
 *	1.	Handling infiles and outfiles through booleans
 *		(infiles and oufiles are not mandatory in a shell command)
 *
 *	2.	read() and open() wont be on a specific argv[] anymore
 *		create a funct that find infiles and outfile
 *
 */

char *init_cmd (t_ctx *ctx, t_cmd *cmd, char **argv)
{
	if (ctx->ac != 5)
		return (ARGC_FAILURE);
	cmd->infile = open(argv[1], O_RDONLY, 0644);
	if (cmd->infile == -1)
		return (IN_FAILURE);
	cmd->outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (cmd->outfile == -1)
		return (OUT_FAILURE);
	if (get_path(cmd) != 0)
		return (ENV_FAILURE);
	return(INIT_SUCCESS);
}

int executing (t_ctx *ctx, t_cmd *cmd, char **argv)
{
	if (ft_strcmp(init_cmd (ctx, cmd, argv), INIT_SUCCESS) != 0)
	{
		ft_putendl_fd(init_cmd(ctx ,cmd, argv), 2);
		return (1);
	}
	return (0);
}

int main (int argc, char **argv, char **envp)
{
	t_cmd *cmd;
	t_ctx *ctx;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);
	ctx = malloc(sizeof(t_ctx));
	if (!ctx)
	{
		free(cmd);
		return (1);
	}

	// TODO : find a more elegant way to add main argument in structures
	ctx->ac = argc;
	ctx->av = argv;
	cmd->env = envp; // actually pointing : should i copy or point ?

	if (executing(ctx, cmd, argv) != 0)
		printf("aie\n");
	else
	{
		printf("path : %s\n", cmd->path);
		int i = 0;
		while (cmd->path_split[i++])
			printf("path_command number %d : %s\n", i, cmd->path_split[i]);
	}
	// int	state;

	return (0);
}