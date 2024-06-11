/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 01:44:42 by Laubry            #+#    #+#             */
/*   Updated: 2023/10/23 16:16:24 by Laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int val, size_t cout)
{
	char	*block;
	int		i;

	block = ptr;
	i = 0;
	while (cout)
	{
		block[i] = (unsigned char)val;
		i++;
		cout--;
	}
	return (block);
}
