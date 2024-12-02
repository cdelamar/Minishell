/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:12:05 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 12:35:27 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*p;
	size_t	i;

	p = (char *)s;
	i = 0;
	while (i < n)
	{
		if (p[i] == (char) c)
			return ((void *)(p + i));
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char tab[] = "Hello World";
	char *result = memchr(tab, 'H', 2);

	if(result != NULL)
		printf("match founded !\n");
	else
		printf("match not founded.\n");

	char tabft[] = "Hello World";
	char *resultft = ft_memchr(tabft, 'H', 2);

	if(resultft != NULL)
		printf("match founded !\n");
	else
		printf("match not founded.\n");
}*/