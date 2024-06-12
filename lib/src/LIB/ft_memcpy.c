/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 01:44:34 by Laubry            #+#    #+#             */
/*   Updated: 2023/10/23 17:10:35 by Laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tadest;
	unsigned char	*tasrc;

	i = 0;
	if (!dest && !src)
		return (NULL);
	tadest = (unsigned char *)dest;
	tasrc = (unsigned char *)src;
	while (i < n)
	{
		tadest[i] = tasrc[i];
		i++;
	}
	return (dest);
}
