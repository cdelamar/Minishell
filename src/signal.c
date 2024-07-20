/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:34:19 by laubry            #+#    #+#             */
/*   Updated: 2024/07/20 02:47:03 by lucasaubry       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_handler(int sig)
{
    if (sig == SIGINT)
	{
        printf("\n");
        rl_on_new_line();
        rl_redisplay();
    }
}

void	signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN); // CTRL + \ interaction
}
