/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:13:06 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 11:53:10 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	loop;

	i = 0;
	j = 0;
	loop = 0;
	if (!*little)
		return ((char *)big);
	while (big[i])
	{
		while (big[i] == little[j] && big[i] && i < len)
		{
			i++;
			j++;
			if (little[j] == '\0')
				return ((char *)&big[i - j]);
		}
		j = 0;
		i = loop++;
	}
	return (NULL);
}

/*int	main(void)
{
	char	tab[] = "dog grad wolf guard";
	char	find[] = "guard";

		char    *ptr;
		ptr = strnstr(tab, find, 8);

//	printf("%s\n", ft_strnstr(tab, find, 8));
	printf("%s\n", ptr);
}*/