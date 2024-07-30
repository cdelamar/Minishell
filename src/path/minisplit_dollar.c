/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisplit_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:15:48 by laubry            #+#    #+#             */
/*   Updated: 2024/07/27 14:44:03 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_in_tab(char **tab_word, char *word)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while(word[j])
	{
		k = 0;
		while(word[j] && word[j] != '$' && word[j] != ' ' && word[j] != '\t')
		{
			tab_word[i][k] = word[j];
			j++;
			k++;
		}
		tab_word[i][k] = '\0';
		if (word[j] == '\0')
		{
			i++;
			tab_word[i] = NULL;
			return ;
		}
		j++;
		i++;
	}
	tab_word[i] = NULL;
}

int	len_of_dollarword(char *word, int i)
{
	int	len;

	len = 0;
	while (word[i] && word[i] != '$')
	{
		len++;
		i++;
	}
	return (len);
}

int	mouve_in_word(char *word, int i)
{
	while (word[i] && word[i] != '$' && word[i] != ' ' && word[i] != '\t')
		i++;
	return (i);
}

int	nbr_of_word(char *word)
{
	int	len;
	int	nbr_of_$word;

	len = 0;
	nbr_of_$word = 0;
	while (word[len])
	{
		if (word[len] == '$')
			nbr_of_$word++;
		len++;
		if (word[len] == '\0')
			nbr_of_$word++;
		if (word[len] == ' ' || word[len] == '\t')
			nbr_of_$word++;
	}
	return (nbr_of_$word);	
}

char	**minisplit_dollar(char *word)
{
	char		**tab_word;
	int			nbr_of_$word;
	int			len;
	int			i;

	i = 0;
	len = 0;
	nbr_of_$word = nbr_of_word(word);
	tab_word = malloc(sizeof(char *) * nbr_of_$word +1);
	while (nbr_of_$word != 0)
	{
		tab_word[len] = malloc(sizeof(char) * len_of_dollarword(word , i) +1);
		i = mouve_in_word(word, i);
		len++;
		nbr_of_$word--;
	}
	copy_in_tab(tab_word, word);
	return (tab_word);
}
