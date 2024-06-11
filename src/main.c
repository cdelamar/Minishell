#include "minishell.h"

void	add_node(t_token *token_list, int argc, char **argv, int i)
{
	t_token *new_node;

	new_node = ft_lstnew(argv[i]);
	if (new_node == NULL)
		return (ERROR_NODE);
	ft_lstadd_back(&token_list, new_node);
}

int	main(int argc ,char **argv)
{
	t_token *token_list = NULL;
	int	i;

	i = -1;
	while (++i != argc -1)
		add_node(token_list, argc, argv, i);
	//free
	ft_lstclear(&token_list, free);
}
