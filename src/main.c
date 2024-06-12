#include "minishell.h"

void	add_node(t_token *token_list, int argc, char **argv, int i)
{
	t_token *new_node;

	new_node = ft_lstnew(argv[i]);
	if (new_node == NULL)
		return (check_error(ERROR_NODE));
	new_node->index = i;// set index
	ft_lstadd_back(&token_list, new_node);
}

/*ATTENTION FAIRE UN SPLITE DE READLNE POUR LE METTRE DANS UN CHAR ** ET SUPPRIMER MAIN
- faire attention au "" et metre tout ce quil y a entre "" dans un seul argument*/
int	main(int argc ,char **argv)
{
	t_token *token_list = NULL;
	t_token *temp = token;
	int	i;

	i = -1;
	while (++i != argc -1)
		add_node(token_list, argc, argv, i);
	//print_node
	lexer(token, argc, argv);


	//free
	ft_lstclear(&token_list, free);
}


tout ce qui suit un commande est un argument jusqua un | ou < >



//-1 metre dans une liste chainee les arguments
//-2
//

echo "-n fjlhgdf"
-n fjlhgdf
echo -n jfjfj pp
jijij
pp
