/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:39:21 by Laubry            #+#    #+#             */
/*   Updated: 2023/11/28 15:39:28 by Laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	ft_puthexa_2(unsigned int nb, char *base)
{
	if (nb >= 16)
		ft_puthexa_2(nb / 16, base);
	ft_putchar_fd(base[nb % 16], 1);
}

int	ft_puthexa(unsigned int nb, char *base)
{
	int	i;

	i = 0;
	ft_puthexa_2(nb, base);
	if (!nb)
		return (1);
	while (nb)
	{
		nb /= 16;
		i++;
	}
	return (i);
}
