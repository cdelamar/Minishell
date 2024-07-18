/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:35:32 by laubry            #+#    #+#             */
/*   Updated: 2024/07/18 15:08:04 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_quote(int i, char *s, char **lst, int j)
{
	int		start;
	int		word_len;
	char	c;

	start = 0;
	word_len = 0;
	if (s[i] == '"')
		c = '"';
	else
		c = '\'';
	start = i;
	i++;
	while (s[i] && s[i] != c)
		i++;
	i++;
	word_len = i - start;
	lst[j++] = ft_substr(s + start, 0, word_len);
	return (i);
}

int	check_is_compar(int i, char *s, char **lst, int j)
{
	char	c;
	int		word_len;
	int		start;

	start = i;
	word_len = 0;
	if (s[i] == '<')
		c = '<';
	else
		c = '>';
	if (s[i + 1] == c)
		i++;
	i++;
	word_len = i - start;
	lst[j] = ft_substr(s + start, 0, word_len);
	return (i);
}

int	check_is_pipe(int i, char *s, char **lst, int j)
{
	lst[j] = ft_substr(s + i, 0, 1);
	return (i + 1);
}

int	check_char(char *s, int i, char **lst, int j)
{
	if (s[i] == '<' || s[i] == '>')
		return (check_is_compar(i, s, lst, j));
	else if (s[i] == '"' || s[i] == '\'')
		return (check_is_quote(i, s, lst, j));
	else if (s[i] == '|')
		return (check_is_pipe(i, s, lst, j));
	else
		return (i);
}
