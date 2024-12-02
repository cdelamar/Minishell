/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:51:59 by laubry            #+#    #+#             */
/*   Updated: 2024/11/30 00:56:20 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*reste(char *start)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!start[i])
		return (NULL);
	str = ft_calloc(ft_strlen(start) + 1, sizeof(char));
	while (start[i])
	{
		if (!ft_isalnum(start[i]) && start[i] != '_')
		{
			while (start[i])
			{
				str[j] = start[i];
				j++;
				i++;
			}
			str[j] = '\0';
			return (str);
		}
		i++;
	}
	return (str);
}

char	*before(char *start)
{
	int		i;
	char	*str;

	str = ft_calloc(ft_strlen(start) + 1, sizeof(char));
	i = 0;
	while (start[i])
	{
		if (!ft_isalnum(start[i]))
		{
			str[i] = '\0';
			return (str);
		}
		str[i] = start[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	getenv_in_list(char **envp, t_token **token)
{
	char	*key;
	char	*rest;
	char	*env_value;
	t_token	*next;

	key = before((*token)->content + 1);
	rest = reste((*token)->content + 1);
	env_value = get_env_value(envp, key);
	free(key);
	if (env_value != NULL)
	{
		update_token_content(*token, env_value, rest);
		return ;
	}
	next = (*token)->next;
	free((*token)->content);
	free(*token);
	*token = next;
	if (rest)
		free(rest);
}

void	path_other(char **envp, t_token **token_list, int place_of_dollar)
{
	t_token	**head;
	char	*signal_str;

	head = token_list;
	while ((*head)->index < place_of_dollar)
		head = &(*head)->next;
	if ((*head)->type == SIMPLE_QUOTE)
		return ;
	if (!ft_strcmp((*head)->content, "$?"))
	{
		free((*head)->content);
		signal_str = malloc(12);
		signal_str = ft_itoa(g_signal);
		(*head)->content = signal_str;
		return ;
	}
	getenv_in_list(envp, head);
}

void	path_main(t_token **token_list, char **envp)
{
	t_token	**head;
	int		place_of_dollar;

	head = token_list;
	while (*head)
	{
		place_of_dollar = find_the_dollar(*head);
		if (place_of_dollar != -1)
			path_other(envp, token_list, place_of_dollar);
		if (*head)
			head = &(*head)->next;
	}
}
