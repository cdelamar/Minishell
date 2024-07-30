/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_boosted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:11:15 by laubry            #+#    #+#             */
/*   Updated: 2024/07/29 14:49:32 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_in_tab(char *s, char **lst)
{
	int	i;
	int	j;
	int	start;
	int	word_len;
	int	in_quote;

	i = 0;
	j = 0;
	word_len = 0;
	start = 0;
	in_quote = 0;
	while (s[i])
	{
		start = i;
		if (skip_space(s, i) != i)
		{	
			i = skip_space(s, i);
			word_len = i - start;
			lst[j] = ft_substr(s + start, 0, word_len);
		}
		else if (check_char(s, i, lst, j) != i)
		{
			free(lst[j]);
			i = check_char(s, i, lst, j);
		}
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
	s = ft_strtrim(s, " ");
	word = count_word(s);
	if (word == 0)
	{
		free(s);
		return (NULL);
	}
	lst = (char **)malloc((word +1) * sizeof(char *));
	if (!lst)
		return (0);
	split_in_tab(s, lst);
	free(s);
	return (lst);
}	

//g g g g gg g"ggggg "
