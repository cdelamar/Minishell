/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 01:43:45 by Laubry            #+#    #+#             */
/*   Updated: 2023/10/24 18:21:30 by Laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		taille;
	int		i;

	i = 0;
	taille = (ft_strlen(s1) + ft_strlen(s2));
	dest = malloc (sizeof(char) * taille + 1);
	if (!dest)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	taille = 0;
	while (s2[taille] != '\0')
	{
		dest[i + taille] = s2[taille];
		taille++;
	}
	dest[i + taille] = '\0';
	return (dest);
}
