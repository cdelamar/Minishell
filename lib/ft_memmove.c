/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:12:15 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 11:55:12 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	front_cpy(char *dest, const char *src, size_t n)
{
	while (n != 0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
}

static void	back_cpy(char *dest, const char *src, size_t n)
{
	dest = dest + (n - 1);
	src = src + (n - 1);
	while (n > 0)
	{
		*dest = *src;
		dest--;
		src--;
		n--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*p_dest;
	char	*p_src;

	p_dest = (char *)dest;
	p_src = (char *)src;
	if (p_dest < p_src)
		front_cpy(p_dest, p_src, n);
	else if (p_dest > p_src)
		back_cpy(p_dest, p_src, n);
	return (dest);
}

/*void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*p_dest;
	char	*p_src;

	p_dest = (char *)dest;
	p_src = (char *)src;
	if (p_dest < p_src)
	{
		while (n != 0)
		{
			*p_dest = *p_src;
			p_dest++;
			p_src++;
			n--;
		}
	}
	else if (p_dest > p_src)
	{
		p_dest = p_dest + (n - 1);
		p_src = p_src + (n - 1);
		while (n > 0)
		{
			*p_dest = *p_src;
			p_dest--;
			p_src--;
			n--;
		}
	}
	return (dest);
}

int	main(void)
{
	char    src[] = "sss sss sss";
	char    dest[40] = "dddsdd";

	memmove(dest, src, 11);
	printf("%s\n", dest);
}*/