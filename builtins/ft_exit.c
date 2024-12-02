/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:13:15 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/23 01:02:25 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isnumber(char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(char **split_line, t_cmd *cmd)
{
	int	exit_code;

	(void)cmd;
	exit_code = 0;
	if (split_line[1] != NULL)
	{
		if (ft_isnumber(split_line[1]))
			exit_code = ft_atoi(split_line[1]);
		else
		{
			fprintf(stderr, "exit : %s : number argument required\n",
				split_line[1]);
			exit_code = -1;
		}
	}
	return (exit_code);
}
