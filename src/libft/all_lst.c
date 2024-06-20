/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:45:29 by laubry            #+#    #+#             */
/*   Updated: 2024/06/20 18:47:14 by lucasaubry       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_lstnew(void *content)
{
	t_token	*chaine;

	chaine = malloc(sizeof(t_token));
	if (!chaine)
		return (NULL);
	chaine->content = content;
	chaine->next = NULL;
	return (chaine);
}

void	token_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*current;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
}

void	token_lstdelone(t_token *lst, void (*del)(void*))
{
	if (!lst ||!del)
		return ;
	del(lst->content);
	free(lst);
}

void	token_lstclear(t_token **lst, void (*del)(void*))
{
	t_token	*dest;

	while (*lst)
	{
		dest = *lst;
		*lst = (*lst)->next;
		token_lstdelone(dest, del);
	}
	*lst = NULL;
}

int	ft_strlen2(char *word)
{
	int	i;

	i = 0;
	while(word[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	while(*s)
	{
		if (*s == (char)c)
			return (char *)s;
		s++;
	}
	if (c == '\0')
		return (char *)s;
	return (NULL);
}

char *ft_strncpy(char *dst, char *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return dst;
}

