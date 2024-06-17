/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:11:04 by laubry            #+#    #+#             */
/*   Updated: 2024/06/14 19:38:16 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_node(t_token **token_list, char **argv, int i)
{
	t_token *new_node;

	new_node = token_lstnew(argv[i]);
	if (new_node == NULL)
		return (check_error(ERROR_NODE));
	new_node->index = i;
	token_lstadd_back(token_list, new_node);
	return (1);
}


void	make_token(char **argv)
{
	t_token *token_list = NULL;
	int	i;
	int	argc;

	argc = nbr_of_argv(argv);
	i = 0;
	while (i < argc)
	{
		if (!add_node(&token_list, argv, i))
			return ;
		i++;
	}
	print_node(token_list);
	lexer(token_list, argv);
}

int	main(int argc ,char **argv)//, char **envp)
{
	char *line;

	(void)argv;
	if (argc > 1)
		return (check_error(ERROR_ARGS));
	while (1)
	{
		line = readline("minishell>");
		make_token(ft_split(line, ' '));// dans le split gerer les "" si tu croise un " ignore les espace et split a patire du prochain " et verifier si il est tout seul
	}



/* 						PARSING
 *  			TRIER LE LEXER ET DONNER DES FD EX...*/







	//free
//	token_lstclear(&token_list, free);
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
