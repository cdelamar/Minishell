/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_boosted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:55:05 by laubry            #+#    #+#             */
/*   Updated: 2024/06/27 18:33:44 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_quote(char *s, int i)
{
	if (s[i] == '"')
	{
		while (s[i] != '"' || s[i])
			i++;
		if (s[i] == '\0')
			return (0); // erreur pas de dexieme "
		//word++;
	}
	else if (s[i] == '\'')
	{
		while (s[i] != '\'' || s[i])
			i++;
		if (s[i] == '\0')
			return (0); // erreur pas de dexieme '
		//word++;
	}
	return (i);
}

void	skip_space(char *s, unsigned long i, int tab[3])
{
	int	word;

	word = 0;
	if (i < ft_strlen(s) || s[i] == ' ')
		word = -1;
	if (s[i] == ' ' || s[i])
	{
		while (s[i] == ' ')
			i++;
	}
	if (s[i] == '\0')
		return ;
	if (word == -1)
		tab[1] = 0;
	else
		tab[1] = 1;
	tab[0] = i;
	tab[2] = 1;
}

//size_t	count_word(char	*s)
//{
//	size_t	word;
//	unsigned long	i;
//	int		tab[3];
//
//	ft_bzero(tab, 3);
//	word = 0;
//	i = 0;
//	while (s[i])
//	{
//		skip_space(s, i, tab);
//		if (tab[2] == 0)
//			return (0); // erreur fin de la chaine apres les espace	
//		i = tab[0];
//		word += tab[1];
//		if (s[i] == '"' || s[i] == '\'')
//		{
//			i = if_quote(s, i);
//			if (i == 0)
//				return (0); // erreur pas de deuxieme quote
//			word++;
//		}
//		i++;	
//	}
//	return (word);
//}



int	is_char(char s)
{
	if (s == ' ' || s == '"' || s == '\'' ||
		   	s == '|' || s == '<' || s == '>' || s == '\0')
		return (0);
	else
		return (1);	
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
			{
				while (s[i] == ' ' && s[i])
					i++;
			}
			else if (s[i] == '"')
			{
				i++;
				while (s[i] != '"' && s[i])
					i++;
				if (s[i] == '\0')
					return (0);
				else
					i++;
				word++;
			}
			else if (s[i] == '\'')
			{
				i++;
				while (s[i] != '\'' && s[i])
					i++;
				if (s[i] == '\0')
					return (0);
				else
					i++;
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



