/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:37:22 by laubry            #+#    #+#             */
/*   Updated: 2024/07/04 18:37:59 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
