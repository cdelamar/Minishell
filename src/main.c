// TODO : add compilation flags

#include "../includes/minishell.h"

// succeed : summon a simple call to one command
// MAIN QUEST : checking for variable expansion ('$')
// SIDE QUEST : checking for free issues
// SIDE QUEST : refactoring lib, especially ft_split

int main(int argc, char **argv, char **envp)
{
	char *line;
	t_cmd *cmd;
	t_ctx *ctx;
	t_token *token;

	if (malloc_structs(&cmd, &ctx, &token) != 0)
	{
		ft_putendl_fd(MALLOC_FAILURE, 2);
		return (1);
	}

	cmd->env = envp;
	while (1)
	{
		line = readline("wzd_sh>");
		if (basic_execute(line, cmd) == EXIT_COMMAND)
		{
			free_structs(cmd, ctx, token);
			free(line);
			return (0);
		}
	}
	free_structs(cmd, ctx, token);
	free(line);
	return (0);
}

