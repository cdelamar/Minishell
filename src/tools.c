/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:27:38 by laubry            #+#    #+#             */
/*   Updated: 2024/06/14 16:46:45 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_node(t_token *token)
{
	t_token *temp = token;

	//temp = temp->next;
	//printf("%d", temp->index);
	while (temp)
	{
		printf("index: %d, content: %s\n", temp->index, temp->content);
		temp = temp->next;
	}
}

int	nbr_of_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
