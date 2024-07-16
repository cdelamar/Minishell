/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:05:29 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/16 17:11:21 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(char **split_line, t_cmd *cmd)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	if (split_line[1] && strncmp(split_line[1], "-n", 2) == 0)
	{
		i++;
		newline = false;
	}
	while (split_line[i])
	{
		if (split_line[i][0] == '>')
			break ;
		ft_putstr_fd (split_line[i], 1);
		i++;
		if (split_line[i])
			ft_putchar_fd (' ', 1);
	}
	if (newline == true)
		ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);
}
