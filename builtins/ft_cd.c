/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:58:38 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/16 17:04:40 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(char *path, t_cmd *cmd)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
		return (1);
	}
	return (0);
}
