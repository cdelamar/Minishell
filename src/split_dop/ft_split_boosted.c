/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_boosted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:11:15 by laubry            #+#    #+#             */
/*   Updated: 2024/07/11 15:51:41 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_in_tab(char *s, char **lst)
{
	int	i;
	int	j;
	int	start;
	int	word_len;

	i = 0;
	j = 0;
	word_len = 0;
	start = 0;
	while (s[i])
	{
	//le PRBLEME VIENT DICI 
		i = skip_space(s, i);
		//if (skip_space(s, i) != i)
		//{
		//	i = skip_space(s, i);
		//	lst[j] = " ";
		//	j++;
		//}
		start = i;
		if (check_char(s, i, lst, j) != i)
			i = check_char (s, i, lst, j);
		else
		{
			while (is_char(s[i]))
				i++;
			word_len = i - start;
			lst[j] = ft_substr(s + start, 0, word_len);
		}
		j++;
	}
	lst[j] = NULL;
}

char	**ft_split_boosted(char *s)
{
	char		**lst;
	int			word;

	lst = NULL;
	word = count_word(s);
	if (word == 0)
		return (NULL);
	lst = (char **)malloc((word +1) * sizeof(char *));
	if (!lst)
		return (0);
	split_in_tab(s, lst);
	return (lst);
}
