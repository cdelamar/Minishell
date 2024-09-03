/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:58:38 by cdelamar          #+#    #+#             */
/*   Updated: 2024/09/03 17:38:47 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int ft_cd(char *path)
{
    if (!path) // Handle case where no argument is provided (e.g., just "cd")
    {
        path = getenv("HOME"); // Get the HOME environment variable
        if (!path) // If HOME is not set, print an error
        {
            ft_putstr_fd("cd: HOME not set\n", 1);
            return (1);
        }
    }

    if (chdir(path) != 0) // Attempt to change directory
    {
        ft_putstr_fd("cd: no such file or directory: ", 1);
        ft_putstr_fd(path, 1);
        ft_putstr_fd("\n", 1);
        return (1);
    }
    return (0);
}

/*
int	ft_cd(char *path)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
		return (1);
	}
	return (0);
}*/
