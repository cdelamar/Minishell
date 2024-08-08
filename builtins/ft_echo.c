/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:05:29 by cdelamar          #+#    #+#             */
/*   Updated: 2024/08/08 13:46:22 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	echo_output(char **split_line, int i)
{
	int	start;

	start = i;
	while (split_line[start])
	{
		ft_putstr_fd(split_line[start], 1);
		start++;
		if (split_line[start])
			ft_putchar_fd(' ', 1);
	}
	return ;
}

int	ft_echo(char **split_line)
{
    int		i;
    int		j;
    bool	newline;

    i = 1;
    newline = true;

	// printf ("** echo **\n");
    while (split_line[i] && split_line[i][0] == '-')
    {
        j = 1;
        while (split_line[i][j] == 'n')
            j++;
        if (split_line[i][j] != '\0')
            break;
        newline = false;
        i++;
    }
    echo_output(split_line, i);
    if (newline)
        ft_putchar_fd('\n', 1);
    return (EXIT_SUCCESS);
}
