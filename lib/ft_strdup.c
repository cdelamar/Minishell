/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:12:37 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 11:54:34 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		size;
	int		i;
	char	*dest;

	size = 0;
	i = 0;
	while (s[size])
	{
		size++;
	}
	dest = (char *)malloc((size + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int	main(void)
{
	char tab_src[] = "test succeed";
	char *tab_dest = strdup(tab_src);

	printf("%s\n", tab_dest);

	char tab_src2[] = "test succeed";
	char *tab_dest2 = ft_strdup(tab_src2);

	printf("%s\n", tab_dest2);

	free(tab_dest);
	free(tab_dest2);
}*/