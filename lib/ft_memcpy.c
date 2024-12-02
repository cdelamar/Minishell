/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:12:12 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 11:55:16 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*p_dest;
	const char	*p_src;

	p_dest = (char *)dest;
	p_src = (const char *)src;
	if (p_dest == p_src)
		return (dest);
	if (p_dest < p_src || p_dest >= (p_src + n))
	{
		while (n--)
			*p_dest++ = *p_src++;
	}
	else
	{
		p_dest += n - 1;
		p_src += n - 1;
		while (n--)
			*p_dest-- = *p_src--;
	}
	return (dest);
}

/*
int	main(void)
{
	char    tab[] = "Test Succeed !";
	char    dest[20];

	memcpy(dest, tab, 14);
	printf("%s\n", dest);

	char    tab2[] = "Test Succeed !";
	char    dest2[20];

	ft_memcpy(dest2, tab2, 14);
	printf("%s\n", dest2);
}*/