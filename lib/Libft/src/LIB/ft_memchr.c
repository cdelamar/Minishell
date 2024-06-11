/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:49:01 by Laubry            #+#    #+#             */
/*   Updated: 2023/10/23 17:08:48 by Laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*sh;

	sh = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (sh[i] == (unsigned char)c)
			return (sh + i);
		i++;
	}
	return (NULL);
}
