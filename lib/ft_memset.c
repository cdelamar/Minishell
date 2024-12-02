/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:12:17 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 15:23:33 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*p;

	i = 0;
	p = s;
	while (i < n)
	{
		p[i] = (char)c;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	char tab[] = "lets go";
	printf("%s\n", tab);
	memset(tab, 'o', 5);
	printf("%s\n", tab);

	char tab2[] = "lets go";
	printf("%s\n", tab2);
	ft_memset(tab2, 'o', 5);
	printf("%s\n",tab2);

}*/
