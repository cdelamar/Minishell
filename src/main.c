/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:11:04 by laubry            #+#    #+#             */
/*   Updated: 2024/06/20 22:05:57 by lucasaubry       ###   ########.fr       */
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


int	make_token(char **argv, t_token *token_list)
{
	int	i;
	int	argc;

	argc = nbr_of_argv(argv);
	if (argc == 0)
		return (0);
	i = 0;
	while (i < argc)
	{
		if (!add_node(&token_list, argv, i))
			return (0);
		i++;
	}	
	print_node(token_list);
	return (1);
}

int	main(int argc ,char **argv, char **envp)
{
	char *line;
	t_token *token_list = NULL;

	(void)argv;
	if (argc > 1)
		return (check_error(ERROR_ARGS));
	while (1)
	{
		line = readline("minishell>");
		if (!check_error_before_split(line))
			return (0);
		//print_path(envp);
		if (!make_token(ft_split(line, ' '), token_list))
			return (0);
		printf("dhzzzzzzzzzzzzdkhd");
		lexer(token_list, argv);
		path_main(token_list, envp);
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
