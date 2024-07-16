/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:35:28 by Laubry            #+#    #+#             */
/*   Updated: 2024/07/16 15:29:56 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone(t_token *lst, void (*del)(void*))
{
	if (!lst ||!del)
		return ;
	del(lst->content);
	free(lst);
}
