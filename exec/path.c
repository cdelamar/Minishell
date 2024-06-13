/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:05:22 by cdelamar          #+#    #+#             */
/*   Updated: 2024/06/13 18:28:24 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*ft_path_finder(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	return (envp[i] + 5);
}

int	ft_path(t_ctx *ctx, t_exec *exec)
{
	exec->paths = ft_path_finder(ctx->envp);
	exec->split_paths = ft_split(exec->paths, ':');
	if (!exec->split_paths)
		return (1);
	return(0);
}
