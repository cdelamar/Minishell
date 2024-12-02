/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:48:45 by laubry            #+#    #+#             */
/*   Updated: 2024/11/22 21:48:47 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char delim)
{
	static char		*stock = NULL;
	char			*ptr;
	int				flg;

	flg = 0;
	ptr = NULL;
	if (str != NULL)
		stock = ft_strdup(str);
	while (*stock != '\0')
	{
		if (flg == 0 && *stock != delim)
		{
			flg = 1;
			ptr = stock;
		}
		else if (flg == 1 && *stock == delim)
		{
			*stock = '\0';
			stock += 1;
			break ;
		}
		stock += 1;
	}
	return (ptr);
}
