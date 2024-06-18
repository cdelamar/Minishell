// TODO : add compilation flags

#include "../includes/minishell.h"

// MAIN QUEST : summon a simple call to one command > OK
// SIDE QUEST : checking for varaible expansion ('$')

int main(int argc, char **argv, char **envp)
{
	char *line;
	t_cmd *cmd;
	t_ctx *ctx;
	t_token *token;

	if (malloc_structs(cmd, ctx, token) != 0)
	{
		ft_putendl_fd(MALLOC_FAILURE, 2);
		return (1);
	}

	cmd->env = envp;
	while (1)
	{
		line = readline("wzd_sh>");
		if (basic_execute(line, cmd) == EXIT_COMMAND)
			return (0);
	}
	free_structs(cmd, ctx, token);
	return (0);
}

