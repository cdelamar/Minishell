/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 00:59:12 by laubry            #+#    #+#             */
/*   Updated: 2024/11/22 19:06:43 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	make_token(char **split_line, t_token **token_list)
{
	int	i;
	int	argc;

	argc = nbr_of_strs(split_line);
	if (argc == 0)
		return (0);
	i = 0;
	while (i < argc)
	{
		if (!add_node(token_list, split_line, i))
			return (0);
		i++;
	}
	lexer(*token_list);
	return (1);
}

char	*tab_to_str(char **tab)
{
	char	*str;
	int		i;

	str = malloc(1);
	i = -1;
	if (!str)
		return (NULL);
	str[0] = '\0';
	while (tab[++i])
	{
		str = ft_realloc_string(str, ft_strlen(tab[i]) + 2);
		if (!str)
			return (NULL);
		ft_strcat(str, tab[i]);
		if (tab[i + 1])
			ft_strcat(str, " ");
	}
	return (str);
}
