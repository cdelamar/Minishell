/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 01:45:21 by Laubry            #+#    #+#             */
/*   Updated: 2023/10/23 22:03:34 by Laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((n == 0 && !s1) || !s2[0])
		return ((char *)s1);
	if (!s1[i])
		return (NULL);
	while (s1[i] && i < n)
	{
		while (s1[i + j] && s1[i + j] == s2[j] && i + j < n)
		{
			j++;
			if (s2[j] == '\0')
				return ((char *)s1 + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
