/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:36:06 by laubry            #+#    #+#             */
/*   Updated: 2024/08/19 18:36:08 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_int(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

char	**replace_x0_to_space(char **finish_tab)
{
	int	i;
	int	j;

	i = 0;
	while (finish_tab[i])
	{
		j = 0;
		while (finish_tab[i][j])
		{
			if (finish_tab[i][j] == '\x01')
				finish_tab[i][j] = ' ';
			else if (finish_tab[i][j] == '\x02')
				finish_tab[i][j] = '\t';
			j++;
		}
		i++;
	}
	return (finish_tab);
}

char	**delet_space_to_tab(char **tab_token)
{
	char	**finish_tab;
	int		len;
	int		i;
	int		j;

	init_int(&len, &i, &j);
	while (tab_token[len])
		len++;
	finish_tab = malloc(sizeof(char *) * (len +1));
	while (i < len)
	{
		if (tab_token[i][0] != ' ' && tab_token[i][0] != '\t')
		{
			finish_tab[j] = malloc(sizeof(char *) * ft_strlen(tab_token[i]));
			ft_strcpy(finish_tab[j], tab_token[i]);
			j++;
		}
		free(tab_token[i]);
		i++;
	}
	free(tab_token);
	finish_tab[j] = NULL;
	finish_tab = replace_x0_to_space(finish_tab);
	return (finish_tab);
}
