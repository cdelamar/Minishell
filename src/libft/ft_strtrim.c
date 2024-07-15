/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:49:20 by laubry            #+#    #+#             */
/*   Updated: 2024/07/15 13:22:34 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	int		i;
	int		j;
	int		res;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr((char *)set, s1[i]))
		i++;
	while (j >= 0 && ft_strchr((char *)set, s1[j]))
		j--;
	if (i > j)
		res = 0;
	else
		res = (j - i) + 1;
	dest = malloc(sizeof(char) * (res + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, (s1 + i), res + 1);
	return (dest);
}
