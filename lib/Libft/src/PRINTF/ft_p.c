/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:51:15 by Laubry            #+#    #+#             */
/*   Updated: 2023/11/28 15:38:48 by Laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_p(void *adresse)
{
	unsigned long long int	add;
	int						i;
	int						len;
	char					add_tab[16];

	len = 0;
	add = (unsigned long long int)adresse;
	if (adresse == NULL)
	{
		ft_putstr("(nil)");
		return (5);
	}
	while (add > 0)
	{
		add_tab[len++] = "0123456789abcdef"[add % 16];
		add /= 16;
	}
	i = len - 1;
	ft_putstr("0x");
	while (i >= 0)
		ft_putchar(add_tab[i--]);
	return (len +2);
}
//while (add > 0) tant que adresse est pas a 0 

//ft_putstr("0x"); une adress commance tjr par 0x
//	while (i >= 0)   on print ladress a lendroit 
//		ft_putchar(add_tab[i--]);  psk de la aut on la print a lenvert
