/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:26:58 by laubry            #+#    #+#             */
/*   Updated: 2024/08/10 02:38:41 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		size;
	char	*dest;

	i = 0;
	size = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup_for_quote(const char *src)
{
	int		i;
	int		size;
	char	*dest;

	i = 0;
	size = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	while (src[i] != '\0')
	{
		if (src[i] == ' ')
			dest[i] = '\x01';
		else if (src[i] == '\t')
			dest[i] = '\x02';
		else
			dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
