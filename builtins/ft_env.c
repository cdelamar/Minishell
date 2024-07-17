/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:11:44 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/17 19:41:07 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf ("je passe bien dans mon env\n");
	while (cmd->env[i])
	{
		ft_putstr_fd(cmd->env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}
