/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:50:12 by cdelamar          #+#    #+#             */
/*   Updated: 2024/06/13 18:28:30 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "exec.h"

int init_exec (t_ctx *ctx, t_exec *exec)
{
	if (ft_path(ctx, exec) == 1)
		return (1);

	return (0);
}

int main (int argc, char **argv, char **envp)
{
	t_exec	exec;
	t_ctx	ctx;
	// init ctx
	ctx.envp = envp;
	// init exec
	// error_checker
}