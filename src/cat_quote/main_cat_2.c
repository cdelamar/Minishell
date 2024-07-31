#include "minishell.h"

void	delet_quote(t_token *token)
{
	while (
}

void	after_before_cat(t_token **token)
{
	t_token	*head;
	int		place;

	place = 0;
	head = *token;
	delet_quote(token);
	while (head != NULL)
	{
		if (head->type == DOUBLE_QUOTE || head->type == SIMPLE_QUOTE)
		{
			process_quotes(token, &place);
			head = *token;
			place = 0;
		}
		place++;
		head = head->next;
	}
	head = *token;
	delet_space_fonc(head);
}

