/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 23:12:25 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/28 00:04:06 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
{
	t_list	*newlst;

	//new_lst = ft_lstnew((*f)lst->content)
	while (lst != NULL)
	{
		newlst = ft_lstnew(f(lst->content));
		if (!newlst)
		{
			ft_lstclear(&lst, del);
			return (NULL);
		}
		ft_lstadd_back(&lst, newlst);
		lst = lst->next;
	}
	return (newlst);
}*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*current;

	newlst = NULL;
	while (lst != NULL)
	{
		current = ft_lstnew(f(lst->content));
		if (!current)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, current);
		lst = lst->next;
	}
	return (newlst);
}
