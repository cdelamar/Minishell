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
	// ain't sure about token allocation due to its linked list nature
	*token = malloc(sizeof(t_token));
	if (!*token)
	{
		free(*cmd);
		free(*ctx);
		return (1);
	}

	//ft_memset(*cmd, 0, sizeof(t_cmd));
    //ft_memset(*ctx, 0, sizeof(t_ctx));
    //(*token)->type = WORD;  // Example initialization for t_token
    //(*token)->value = NULL;
    //(*token)->next = NULL;
	return (0);
}
void free_structs(t_cmd *cmd, t_ctx *ctx, t_token *token)
{
	if(cmd->path_split)
		ft_freetab(cmd->path_split);
	if(cmd)
	{
		printf("free cmd\n");
		free(cmd);
	}
	if(ctx)
	{
		printf("free ctx\n");
		free(ctx);
	}
	if(token)
	{
		printf("free cmd\n");
		free(token);
	}
}