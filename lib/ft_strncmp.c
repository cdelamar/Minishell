/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:13:00 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 11:53:30 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		++i;
	}
	if (i != n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

/*
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;
	int	size;

	i = 0;
	size = (int)n;
	if (size == 0)
		return(0);
	while(s1[i] == s2[i] && s1[i] && s2[i] && i < size - 1)
	{
		i++;
	}
	return(s1[i] - s2[i]);
}

int	main(void)
{
	char tab1[] = "test\200";
	char tab2[] = "test\0";

	printf("my function :%d\n", ft_strncmp(tab1, tab2, 6));
	printf("original : %d\n", strncmp(tab1, tab2, 6));
}*/