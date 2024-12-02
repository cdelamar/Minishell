/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_boosted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:11:15 by laubry            #+#    #+#             */
/*   Updated: 2024/11/15 23:44:40 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_sub(char **lst, char *s, int *i, int *j)
{
	int	start;
	int	word_len;

	word_len = 0;
	start = *i;
	*i = skip_space(s, *i);
	word_len = *i - start;
	lst[*j] = ft_substr(s + start, 0, word_len);
}

void	skip_char(char **lst, int *j, int *i, char *s)
{
	free(lst[*j]);
	*i = check_char(s, *i, lst, *j);
}

void	word_sub(char **lst, int *j, int *i, char *s)
{
	int	start;
	int	word_len;

	start = *i;
	while (is_char(s[*i], 0))
		(*i)++;
	word_len = *i - start;
	lst[*j] = ft_substr(s + start, 0, word_len);
}

void	split_in_tab(char *s, char **lst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (skip_space(s, i) != i)
			skip_sub(lst, s, &i, &j);
		else if (check_char(s, i, lst, j) != i)
			skip_char(lst, &j, &i, s);
		else
			word_sub(lst, &j, &i, s);
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
	lst = modif_pipe(lst);
	return (lst);
}
