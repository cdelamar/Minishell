/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:12:09 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 11:55:19 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	i = 0;
	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	if (str1 == str2 || n == 0)
		return (0);
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char tab[] = "test";
	char check[] = "tect";

	int res = memcmp(tab, check, 3);

	if (res < 0)
		printf("tab < check\n");
	else if (res > 0)
		printf("tab > check\n");
	else
		printf("tab == check\n");

	// ft version

	printf("%d\n", res);

	int resft = ft_memcmp(tab, check, 3);

	if (resft < 0)
		printf("tab < check\n");
	else if (resft > 0)
		printf("tab > check\n");
	else
		printf("tab == check\n");

	printf("%d\n", res);

	return (0);
}*/