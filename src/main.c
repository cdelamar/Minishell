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

	while (1)
	{
		if (malloc_structs(&cmd, &ctx, &token) != 0)
		{
			ft_putendl_fd(MALLOC_FAILURE, 2);
			return (1);
		}

		cmd->env = envp;
		line = readline("minigroseille>");
		if (execute(line, cmd) == EXIT_COMMAND) // define OK ?
		{
			free_structs(cmd, ctx, token);
			free(line);
			return (0);
		}
		free_structs(cmd, ctx, token);
	}
	free_structs(cmd, ctx, token);
	free(line);
	return (0);
}

