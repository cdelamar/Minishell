/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:12:34 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 11:54:38 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}
/*
int	main(void)
{
	char tab[] = "hello bonjour";
	char *res;
	res = strchr(tab, 'o');

	char *resft;
	resft = ft_strchr(tab, 'o');

	printf("%s found at %p\n", res, (void *) res);
	printf("%s found at %p\n", resft, (void *)resft );

}*/