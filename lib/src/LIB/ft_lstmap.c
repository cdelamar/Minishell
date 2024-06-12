/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:28:49 by Laubry            #+#    #+#             */
/*   Updated: 2023/10/27 15:27:44 by Laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*tmp;
	t_list	*temp;

	if (!lst)
		return (NULL);
	tmp = lst;
	newlist = ft_lstnew((*f)(tmp->content));
	if (!newlist)
		return (NULL);
	tmp = tmp->next;
	while (tmp != NULL)
	{
		temp = ft_lstnew((*f)(tmp->content));
		if (!temp)
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, temp);
		tmp = tmp->next;
	}
	return (newlist);
}
