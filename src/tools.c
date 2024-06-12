#include "minishell.h"

void	print_node(t_token *token)
{
	t_token *temp = token;

	while (temp)
	{
		printf("index: %d, content: %d\n", temp->index, temp->content);
		temp = temp->next;
	}
}
