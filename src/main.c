/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:11:04 by laubry            #+#    #+#             */
/*   Updated: 2024/07/18 02:59:58 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_var = 0;

int	add_node(t_token **token_list, char **strs, int i)
{
	t_token	*new_node;

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
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**split_line;
	t_token	*token_list;

	token_list = NULL;
	(void)argv;
	if (argc > 1)
		return (check_error(ERROR_ARGS));
	print_snail();
	while (1)
	{
		line = readline("minishell>");
		printf("%zu\n", count_word(line));
		split_line = ft_split_boosted(line);
		if (split_line == NULL)
			return (0);
		free(line);
		if (!make_token(split_line, &token_list))
			return (0);
		path_main(token_list, envp);
		after_before_cat(&token_list);
		print_node(token_list);
		token_lstclear(&token_list, free);
	}
}
// $? pas fini enfin si mais pas sur
//le realoc tu doit le recoder dans parsing.c
