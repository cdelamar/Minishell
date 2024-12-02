/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_of_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:02:27 by laubry            #+#    #+#             */
/*   Updated: 2024/11/22 19:00:23 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_prefix(char *word)
{
	int	i;

	i = 0;
	while (word[i] != '$')
		i++;
	return (i +1);
}

int	find_the_dollar(t_token *token)
{
	while (token)
	{
		if (ft_strchr2(token->content, '$') == 1)
			return (token->index);
		token = token->next;
	}
	return (-1);
}

void	update_token_content(t_token *token, char *env_value, char *rest)
{
	char	*new_content;

	if (rest != NULL)
	{
		new_content = ft_strjoin(env_value, rest);
		free(rest);
	}
	else
		new_content = ft_strdup(env_value);
	free(token->content);
	token->content = new_content;
}

char	*get_env_value(char **envp, const char *key)
{
	size_t	len;

	len = ft_strlen(key);
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, key, len) == 0 && (*envp)[len] == '=')
			return (*envp + len + 1);
		envp++;
	}
	return (NULL);
}
