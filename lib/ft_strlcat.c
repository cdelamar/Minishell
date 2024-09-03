/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:12:46 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 11:54:21 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)

{
	size_t	src_len;
	size_t	dest_len;
	size_t	i;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	i = 0;
	if (size <= dest_len)
		return (src_len + size);
	while (src[i] && (dest_len + i) < (size - 1))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = 0;
	return (src_len + dest_len);
}

/*{
	size_t	i;
	size_t	j;
	size_t	len_dest;
	size_t	len_src;

	i = 0;
	j = 0;
	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);


	if(size == 0)
		return(len_src);
	while(dest[i])
		i++;
	while(src[j] && (len_dest + j) <= size)
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';
	return (len_dest + len_src);
}

int	main(void)
{
	char dest[50] = "1234";
	char src[] = "56789";

	char dest2[50] = "1234";
	char src2[] = "56789";

	size_t res =  strlcat(dest, src, 19);
	size_t ft_res =  ft_strlcat(dest2, src2, 19);


	strlcat(dest, src, sizeof(dest));
	ft_strlcat(dest2, src2, sizeof(dest2));

	printf("\n_----__----___----_\n\nvanilla :\n >> %s\n\n", dest);
	printf("custom :\n >> %s\n\n", dest2);
	printf("strlcat  : %ld\n", res);
	printf("ft_strlcat  : %ld\n", ft_res);

	return (0);
}*/