/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:42:17 by laubry            #+#    #+#             */
/*   Updated: 2024/07/11 18:11:00 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error(int code_error)
{
	if (code_error == ERROR_NODE)
		printf("node creation error");
	else if (code_error == ERROR_ARGS)
		printf("error arguments");
	else if (code_error == ERROR_QUOTE)
		printf("error solo quote detected");
	return (0);
}

int	check_quote_error(char *line)
{
	int	tab[3];
	int	i;

	ft_bzero(tab, sizeof(tab));
	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			if (!tab[1])
				tab[2] = !tab[2];
		}
		else if (line[i] == '\'')
		{
			if (!tab[2])
				tab[1] = !tab[1];
		}
		i++;
	}
	if (tab[2] || tab[1])
		return (1);
	return (check_error(ERROR_QUOTE));
}
