/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 01:55:26 by laubry            #+#    #+#             */
/*   Updated: 2024/11/19 19:41:04 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_line(char *line, char **split_line)
{
	if (space_only(line) == true)
	{
		free (line);
		return (0);
	}
	if (ft_strcmp(split_line[0], "|") == 0)
	{
		printf("synthax error near \"|\"\n");
		free_split_line(split_line);
		g_signal = 2;
		free(line);
		return (0);
	}
	if (solo_quote(split_line) || badchar(split_line) || qte(split_line)
		|| !check_pipe(split_line))
	{
		g_signal = 127;
		if (!check_pipe(split_line))
			printf("syntax error near \"||\"\n");
		else
			printf("synthax error : unmatching quote\n");
		free_split_line(split_line);
		return (0);
	}
	return (1);
}

int	verif_make_token(char *line, char **split_line, t_token **token_list)
{
	if ((line == NULL) || (!make_token(split_line, token_list)))
	{
		free_split_line(split_line);
		g_signal = 0;
		return (0);
	}
	return (1);
}
