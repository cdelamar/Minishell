/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:13:08 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 12:27:48 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)

{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			ptr = (char *)(s + i);
		i++;
	}
	if (s[i] == (char)c)
		ptr = (char *)(s + i);
	return (ptr);
}
/*
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (char) c)
			return (&(str[i]));
		if (i == 0)
			return (NULL);
		i--;
	}
	return (NULL);
}*/
/*
int main()
{
	char tab[] = "hello, is it me youre looking for ?";
	char *res;
	res = strrchr(tab, 'o');



	char *resft;
	resft = ft_strrchr(tab, 'o');

	char *rres;
	rres = strchr(tab, 'o');

	printf("\n\nstrrchr >> -%s- founded, location : %p\n\n", res, res);

	printf("ft_strrchr >> -%s- founded, location : %p\n\n", resft, resft);

	printf("strchr >> -%s- founded, location : %p\n\n", rres, rres);
}*/