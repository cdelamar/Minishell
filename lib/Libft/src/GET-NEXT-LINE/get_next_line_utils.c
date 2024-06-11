/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:23:06 by laubry            #+#    #+#             */
/*   Updated: 2024/02/16 14:01:50 by Laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_char(char *src, char c)
{
	int	i;

	i = 0;
	if (src == NULL)
		return (0);
	while (src[i] != '\0' && src[i] != c)
		i++;
	return (i);
}

char	*ft_strjoin_and_free_s1_2(char *s1, char *dest)
{
	if (dest == NULL)
		return (NULL);
	if (s1 != NULL)
		free(s1);
	if (dest[0] == '\0')
	{
		free(dest);
		return (NULL);
	}
	return (dest);
}
