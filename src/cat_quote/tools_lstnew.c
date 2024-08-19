/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lstnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:41:07 by laubry            #+#    #+#             */
/*   Updated: 2024/08/19 18:41:15 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_space_node(char **str, int i)
{
	int	j;

	j = 0;
	if (str[i] == NULL)
		return (0);
	while (str[i][j] && str[i])
	{
		if (str[i][j] != ' ' && str[i][j] != '\t' && str[i][j] != '|'
				&& str[i][j] != '>' && str[i][j] != '<')
			return (0);
		j++;
	}
	return (1);
}

char	**mouve_str(char **str, int i)
{
	int	j;

	j = i + 1;
	while (str[j])
	{
		str[i] = str[j];
		str[j] = NULL;
		i++;
		j++;
	}
	return (str);
}
