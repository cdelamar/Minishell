/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:51:59 by laubry            #+#    #+#             */
/*   Updated: 2024/08/19 19:03:13 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_in_tab(t_token *token_list, char *start)
{
	int		i;
	char	*s;
	char	*lst;

	i = 0;
	while (token_list->content[i] != '$')
		i++;
	s = malloc(sizeof(char) * i +1);
	i = 0;
	while (token_list->content[i] != '$')
	{
		s[i] = token_list->content[i];
		i++;
	}
	s[i] = '\0';
	free(token_list->content);
	lst = ft_strjoin(s, start);
	free(s);
	return (lst);
}

void	getenv_in_list(char **envp, t_token *token_list, char *word, int plc)
{
	char		**env;
	size_t		len;
	char		*start;
	int			old_enum;

	env = envp;
	len = ft_strlen(word);
	while (*env != NULL)
	{
		if (ft_strncmp(*env, word, len) == 0 && (*env)[len] == '=')
		{
			start = *env + len +1;
			while (plc != token_list->index)
				token_list = token_list->next;
			old_enum = token_list->type;
			token_list->content = path_in_tab(token_list, start);
			token_list->type = old_enum;
			break ;
		}
		env++;
	}
}

void	path_other(char **envp, t_token *token_list, int place_of_dollar)
{
	t_token	*head;
	int		prefix;

	head = token_list;
	while (head->index < place_of_dollar)
		head = head->next;
	if (head->type == SIMPLE_QUOTE)
		return ;
	prefix = skip_prefix(head->content);
	getenv_in_list(envp, token_list, head->content + prefix, place_of_dollar);
}

void	path_main(t_token *token_list, char **envp)
{
	t_token	*head;
	int		place_of_dollar;

	head = token_list;
	while (head)
	{
		place_of_dollar = find_the_dollar(head);
		if (place_of_dollar != -1)
			path_other(envp, token_list, place_of_dollar);
		head = head->next;
	}
}
