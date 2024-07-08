/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:11:04 by laubry            #+#    #+#             */
/*   Updated: 2024/07/08 12:09:46 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_node(t_token **token_list, char **strs, int i)
{
	t_token *new_node;

	new_node = token_lstnew(strs[i]);
	if (new_node == NULL)
		return (check_error(ERROR_NODE));
	new_node->index = i;
	token_lstadd_back(token_list, new_node);
	return (1);
}

int	make_token(char **strs, t_token **token_list)
{
	int	i;
	int	argc;

	argc = nbr_of_strs(strs);
	if (argc == 0)
		return (0);
	i = 0;
	while (i < argc)
	{
		if (!add_node(token_list, strs, i))
			return (0);
		i++;
	}	
	lexer(*token_list, strs);
//	print_node(*token_list);
	return (1);
}

int	main(int argc ,char **argv, char **envp)
{
	char *line;
	char **split_line;
	t_token *token_list = NULL;

	(void)argv;
	if (argc > 1)
		return (check_error(ERROR_ARGS));
	while (1)
	{
		line = readline("minishell>");
		//print_path(envp);
		printf("%zu\n", count_word(line));
		split_line = ft_split_boosted(line);
		if (split_line == NULL)
			return(0);
		if (!make_token(split_line, &token_list))
			return (0);
		path_main(token_list, envp);
		print_node(token_list);
		token_lstclear(&token_list, free);
	}



/* 						PARSING
 *  			TRIER LE LEXER ET DONNER DES FD EX...*/

//gere les ? apres les $ il revoie la dernier erreur
// si il y a ""apres $ c laubry si cest '' cest user



	//le realoc tu doit le recoder dans parsing.c

	//free
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
