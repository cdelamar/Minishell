/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 01:58:29 by Laubry            #+#    #+#             */
/*   Updated: 2023/11/28 14:43:32 by Laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_verif(va_list list, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(list, int));
	else if (format == 's')
		len += ft_putstr(va_arg(list, char *));
	else if (format == 'p')
		len += ft_p(va_arg(list, void *));
	else if (format == 'd')
		len += ft_putnbr(va_arg(list, int));
	else if (format == 'i')
		len += ft_putnbr(va_arg(list, int));
	else if (format == 'u')
		len += ft_putunbr(va_arg(list, unsigned int));
	else if (format == 'x')
		len += (ft_puthexa(va_arg(list, unsigned int), "0123456789abcdef"));
	else if (format == 'X')
		len += (ft_puthexa(va_arg(list, unsigned int), "0123456789ABCDEF"));
	else if (format == '%')
		return (ft_putchar('%'));
	return (len);
}

int	ft_printf(const char*format, ...)
{
	va_list	list;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start (list, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			len += ft_verif(list, format[i + 1]);
			i++;
		}
		else
			len += ft_putchar(format[i]);
		i++;
	}
	va_end (list);
	return (len);
}
