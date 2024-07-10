/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:27:38 by laubry            #+#    #+#             */
/*   Updated: 2024/07/10 18:50:00 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_node(t_token *token)
{
	t_token *temp = token;
	while (temp)
	{
		printf("temp: %p, index: %d, content: %s, type: %d\n",temp, temp->index, temp->content, temp->type);
		temp = temp->next;
	}
}

void	print_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

int	nbr_of_strs(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
