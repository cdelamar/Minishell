// TODO : add compilation flags

#include "../includes/minishell.h"

// MAIN QUEST : proper loop error handling

// SIDE QUEST : find out grep issue > DOESNT WORK WITH DOUBLE QUOTES

int main(int argc, char **argv, char **envp)
{
	char *line;
	t_cmd *cmd;
	t_ctx *ctx;
	t_token *token;

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
		line = readline("minishell>");

		// CTRL + D
		if (line == NULL)
		{
			free_structs(cmd, ctx, token);
			return (0);
		}

		// HISTORY LINE
		if (*line)
			add_history(line);

		// EXECUTING
		if (execute(line, cmd) == EXIT_COMMAND) // define OK ?
		{
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

