/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_boosted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:55:05 by laubry            #+#    #+#             */
/*   Updated: 2024/06/28 11:35:27 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_char(char s)
{
	if (s == ' ' || s == '"' || s == '\'' ||
		   	s == '|' || s == '<' || s == '>' || s == '\0')
		return (0);
	else
		return (1);	
}

int	is_quote(char *s, int i)
{
	char	c;

	c = '\0';
	if (s[i] == '"')
		c = '"';
	else if (s[i] == '\'')
		c = '\'';
	i++;
	while (s[i] != c && s[i])
		i++;
	if (s[i] == '\0')
		return (0);
	i++;
	return (i);
}

int	skip_space(char *s, int i)
{
	while (s[i] == ' ' && s[i])
		i++;
	return (i);
}
size_t	count_word(char *s)
{
	size_t	word;
	int		i;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (!is_char(s[i]))
		{
			if (s[i] == '\0')
				return (0);
			if (s[i] == ' ')
				i = skip_space(s, i);
			else if (s[i] == '"' || s[i] == '\'')
			{
				i = is_quote(s, i);	
				if (i == 0)
					return (0);
				word++;
			}
			else if (s[i] == '|' || s[i] == '>' || s[i] == '<')
			{
				word++;
				i++;
			}
		}
		else if (ft_isalpha(s[i]))
		{
			while (ft_isalpha(s[i]))
				i++;
			word++;
		}
		else
			return (0);
	}
	return (word);
}

//si echo"oui" print echooui en faite les "" concataine meme deriere

char **ft_split_boosted(char *s)
{
	char	**lst = NULL;
//
//	lst = (char **)malloc((count_word(s) +1) * sizeof(char *));
//	if (!lst || !s)
//		return (0); // erreur malloc ou chaine vide
	printf("%zu\n", count_word(s));
	return (lst);
}



