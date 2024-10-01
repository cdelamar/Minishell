/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:06:47 by cdelamar          #+#    #+#             */
/*   Updated: 2024/10/01 21:10:12 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO handle 'exit 0 | exit 1'

// memory :
// still reachable :    'ls | dqwdqwdqwd'
// still reachable :	'qdwdqwqdwqwd | ls"
// invalid read :       'wfekljfweljkljkwef'

// major :
// handle 'qwwqls | wc' : FIND OUT WHY PIPE DOESNT CHECK 1ST COMMAND

// minor :
// handle 'sort << "" '
// handle 'cat <test.txt'

#include "../includes/minishell.h"

volatile sig_atomic_t g_signal = 0;


// ??? faut free dans pipe exec cest sur

static void process_input(char *line, t_cmd *cmd)
{
	if (line == NULL)
	{
		//printf("CTRL + D from shell_loop\n");
		ft_freetab(cmd->env);
		free_structs(cmd);
		exit(0); // Handle exit on EOF (CTRL + D)
	}

	if (space_only(line) == true)
	{
		//free_structs(cmd);
		return;
	}

	if (*line)
		add_history(line);

	execute(line,cmd); // execute retourne un int mais je men sert pas
}

char **cpy_tab(char **dest, char **src)
{
	int len = -1;
	while (src[++len])
		dest[len] = ft_strdup(src[len]);
	dest[len] = NULL;
	return dest;
}

void shell_exec_loop(char **envp)
{
	char	*line;
	t_cmd	*cmd = NULL;
	int		len = -1;

	while (envp[++len]) {}
	char **tab = malloc(sizeof(char *) * (len + 1));
	cpy_tab(tab, envp);
	while (1)
	{
		if (malloc_structs(&cmd) != 0)
		{
			ft_putendl_fd(MALLOC_FAILURE, 2);
			return ;
		}
		cmd->heredoc_processed = FALSE;
		cmd->env = tab;
		line = readline("$ ");
		process_input(line, cmd);
		free(line); // LEAK
		tab = cmd->env;
	}
}

int main(int argc, char **argv, char **envp)
{
	// g_signal = 0;
	(void)argv;

	if (argc != 1)
	{
		printf("invalid argument.\n");
		return (0);
	}
	rl_outstream = stderr;

	signals();

	shell_exec_loop(envp);
	return 0;
}

