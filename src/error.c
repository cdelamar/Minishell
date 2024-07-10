/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:42:17 by laubry            #+#    #+#             */
/*   Updated: 2024/07/10 18:42:33 by laubry           ###   ########.fr       */
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
	int	in_simple_quote;
	int	in_dbl_quote;
	int	simple_count;
	int	dbl_count;
	int	i;

	i = 0;
	in_simple_quote = 0;
	in_dbl_quote = 0;
	simple_count = 0;
	dbl_count = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			if (!in_simple_quote)
			{
				in_dbl_quote = !in_dbl_quote;
				if (!in_dbl_quote)
					dbl_count++;
			}
		}
		else if (line[i] == '\'')
		{
			if (!in_dbl_quote)
			{
				in_simple_quote = !in_simple_quote;
				if (!in_simple_quote)
					simple_count++;
			}
		}
		i++;
	}
	if (dbl_count % 2 != 0 || simple_count % 2 != 0)
	{
		return (1);
	}
	check_error(ERROR_QUOTE);
	return (0);
}

int	check_error_before_split(char *line)
{
	if (check_quote_error(line) != 0)
		return (0);
	return (1);
}
