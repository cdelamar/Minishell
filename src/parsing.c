#include "minishell.h"



// atribu un enum au args
token_enum	assign_enum(t_token, index)
{
	int	i;
	t_token *temp;

	i = -1;
	temp = token;
	while(++i != index) // va jusqua la lindex pour lui atribuer un enum
		temp = temp->next;
	if (strcmp(token.content, "|") == 0)
	   return (PIPE);
	else if (strcmp(token.content, "<") == 0 || strcmp(token.content, ">") == 0 ||
		   	strcmp(token.content, ">>") == 0 || strcmp(token.content, "<<") == 0)
		return (REDIRECTION);
	else if (!*token.content) // si largument c un \0
		return (END);
	else
		return (WORD);

}


//lexer = metre tout dans une liste chainee et metre des enum sur les args
void	lexer(t_token *token, int argc, char **argv)
{
	int	i;
	int	index;
	t_token *head;

	i = 0;
	index = 0;
	head = token;
	while(token)
	{
		token->content = argv[i];
		token = token->next;
		i++;
	}
	token = head;
	while(token)
	{
		token->type = assign_enum(token, index);
		token = token->next;
		index++;
	}	

}
