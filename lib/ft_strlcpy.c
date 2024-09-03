/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:12:50 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 11:54:14 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_cpy;

	i = 0;
	len_cpy = ft_strlen(src);
	if (!dst && !src)
		return (0);
	if (size > 0)
	{
		while (i + 1 < size && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len_cpy);
}
/*
int	main(void)
{
	char	tab[] = "";
	char	tabtest[20];
	char	tabtest2[20];

	tabtest[0] = '\0';
	tabtest2[0] = '\0';
	ft_strlcpy(tabtest, tab, 3);
	strlcpy(tabtest2, tab, 3);
	printf("ft_strlcpy : %s$\n", tabtest);
	printf("strlcpy : %s$\n", tabtest2);

	return (0);
}*/