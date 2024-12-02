/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:12:32 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 11:54:41 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_split_count(const char *str, char c)
{
	int	i;
	int	output;

	if (!str)
		return (0);
	i = 0;
	output = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
			output++;
		while (str[i] != c && str[i])
			i++;
	}
	return (output);
}

char	**ft_split(const char *str, char c)
{
	char	**output;
	int		start;
	int		size;
	int		i;

	output = malloc((ft_split_count(str, c) + 1) * sizeof(char *));
	if (!output)
		return (NULL);
	start = 0;
	size = 0;
	i = 0;
	while (str[start + size])
	{
		start += size;
		while (str[start] == c && str[start])
			start++;
		size = 0;
		while (str[start + size] != c && str[start + size])
			size++;
		if (size)
			output[i++] = ft_substr(str, start, size);
	}
	output[i] = NULL;
	return (output);
}
