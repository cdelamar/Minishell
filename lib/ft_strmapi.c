/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:12:58 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 15:27:38 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	str = (char *)malloc(ft_strlen(s) * sizeof(char) + 1);
	i = 0;
	if (!s || !f || !str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
int     main()
{
		char tab[] = "jai la peche";
		printf("%s\n", tab);

		printf("%s\n", ft_strmapi(tab, ft_toupper));
		printf("%s\n", tab);

		return (0);
}*/