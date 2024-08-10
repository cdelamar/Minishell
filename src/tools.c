/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:27:38 by laubry            #+#    #+#             */
/*   Updated: 2024/08/08 17:05:15 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_node(t_token *token)
{
    t_token *temp = token;
    while (temp)
    {
        if (temp->content)
        {
            printf("temp: %p, index: %d, content: %s, type: %d\n", temp, temp->index, temp->content, temp->type);
        }
        else
        {
            printf("temp: %p, index: %d, content: (null), type: %d\n", temp, temp->index, temp->type);
        }
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

void	print_split(char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
	{
		printf("print_split :%s\n", split_line[i]);
		i++;
	}
}

int	is_qte(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}
