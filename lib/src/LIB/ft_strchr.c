/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 01:44:45 by Laubry            #+#    #+#             */
/*   Updated: 2023/10/23 21:52:02 by Laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] && str != NULL)
	{
		if (str[i] == (const char)c)
			return ((char *)str + i);
		i++;
	}
	if (str[i] == (const char)c)
		return ((char *)str + i);
	return (NULL);
}
