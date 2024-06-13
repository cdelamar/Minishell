/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:11:04 by laubry            #+#    #+#             */
/*   Updated: 2024/06/13 19:29:05 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_node(t_token **token_list, char **argv, int i)
{
	t_token *new_node;

	new_node = token_lstnew(argv[i]);
	if (new_node == NULL)
		return (check_error(ERROR_NODE));
	new_node->index = i;// set index
	//printf("%d", new_node->index);
	token_lstadd_back(token_list, new_node);
	return (1);
}

/*ATTENTION FAIRE UN SPLITE DE READLNE POUR LE METTRE DANS UN CHAR ** ET SUPPRIMER MAIN
- faire attention au "" et metre tout ce quil y a entre "" dans un seul argument*/
int	main(int argc ,char **argv)
{
	t_token *token_list = NULL;
	int	i;

	i = 0;
	while (i < argc)
	{
		if (!add_node(&token_list, argv, i))
			return (0);
		i++;
	}
	print_node(token_list);
	lexer(token_list, argv);


	//free
	token_lstclear(&token_list, free);
}


//tout ce qui suit un commande est un argument jusqua un | ou < >



//-1 metre dans une liste chainee les arguments
//-2
//


//echo "-n fjlhgdf"
//-n fjlhgdf
//echo -n jfjfj pp
//jijij
//pp
