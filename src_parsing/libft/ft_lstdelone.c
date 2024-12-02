/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:35:28 by Laubry            #+#    #+#             */
/*   Updated: 2024/07/18 17:06:29 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone(t_token *lst, void (*del)(void*))
{
	if (lst != NULL)
	{
		if (del != NULL && lst->content != NULL)
			del(lst->content);
		free(lst);
	}
}
