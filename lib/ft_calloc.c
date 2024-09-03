/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:11:29 by cdelamar          #+#    #+#             */
/*   Updated: 2024/04/24 22:39:59 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_memset((unsigned char *)ptr, 0, nmemb * size);
	return (ptr);
}
/*
int	main(void)
{
	size_t test = 8;
	size_t size = sizeof(int);
	int i = 1;

	int *ptr_ft;
	int *ptr_man;

	ptr_ft = (int *)ft_calloc(test, size);
	ptr_man = (int *)calloc(test, size);

	while (i < test)
	{
		ptr_ft[i] = i;
		ptr_man[i] = i;
		i++;
	}

	if(ft_memcmp(ptr_man, ptr_ft, test * size) == 0)
		printf("OK\n");
	else
		printf("Fail\n");

	free(ptr_ft);
	free(ptr_man);

	return (0);
}*/