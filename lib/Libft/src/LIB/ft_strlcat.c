/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 01:44:59 by Laubry            #+#    #+#             */
/*   Updated: 2023/10/23 17:14:01 by Laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	tsrc;
	size_t	tdest;

	i = 0;
	tsrc = ft_strlen(src);
	tdest = ft_strlen(dest);
	if (size == 0)
		return (tsrc);
	while (src[i] && tdest + i < (size - 1))
	{
		dest[i + tdest] = src[i];
		i++;
	}
	if (i < size)
		dest[i + tdest] = '\0';
	if (tdest > size)
		return (size + tsrc);
	return (tdest + tsrc);
}
