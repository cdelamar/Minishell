/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:05:29 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/09 14:02:07 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	echo_output(char **split_line, int i)
{
	int	start;

	start = i;
	while (split_line[start])
	{
		if (ft_strchr(split_line[start], '\x1F'))
		{
			skip_x1f(split_line[start]);
			start++;
		}
		else
		{
			ft_putstr_fd(split_line[start], 1);
			start++;
			if (split_line[start])
				ft_putchar_fd(' ', 1);
		}
	}
	return ;
}

int	handle_flags(char **split_line, bool *newline, int i)
{
	int	j;

	while (split_line[i] && split_line[i][0] == '-')
	{
		j = 1;
		while (split_line[i][j] == 'n')
			j++;
		if (split_line[i][j] != '\0')
			break ;
		*newline = false;
		i++;
	}
	return (i);
}

int	echo_no_arguments(bool newline)
{
	if (newline)
		ft_putchar_fd('\n', 1);
	g_signal = 0;
	return (EXIT_SUCCESS);
}

void	echo_with_arguments(char **split_line, int i, bool newline)
{
	echo_output(split_line, i);
	if (newline)
		ft_putchar_fd('\n', 1);
}

int	ft_echo(char **split_line)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	i = handle_flags(split_line, &newline, i);
	if (split_line[i] == NULL)
		return (echo_no_arguments(newline));
	else
		echo_with_arguments(split_line, i, newline);
	g_signal = 0;
	return (EXIT_SUCCESS);
}
