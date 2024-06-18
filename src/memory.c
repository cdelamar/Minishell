#include "../includes/minishell.h"

int malloc_structs(t_cmd *cmd, t_ctx *ctx, t_token *token)
{
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);
	ctx = malloc(sizeof(t_ctx));
	if (!ctx)
	{
		free(cmd);
		return (1);
	}
	// ain't sure about token allocation due to its linked list nature
	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(cmd);
		free(ctx);
		return (1);
	}
	return (0);
}
// CAREFUL WITH DOUBLE FREES
void free_structs(t_cmd *cmd, t_ctx *ctx, t_token *token)
{
	free(cmd);
	free(ctx);
	free(token);
}