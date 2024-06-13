/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:42:03 by cdelamar          #+#    #+#             */
/*   Updated: 2024/06/13 16:43:26 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pointer;
	int		result;

	pointer = NULL;
	result = nmemb * size;
	if (!nmemb || !size || nmemb == result / size)
		pointer = malloc(result);
	if (pointer)
		while (result--)
			*(unsigned char *)(pointer + result) = 0;
	return (pointer);
}

char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == (char)c)
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*string;
	size_t	length;

	length = ft_strlen(s1);
	if (!s1 || !s2)
		return (NULL);
	string = ft_calloc(length + ft_strlen(s2) + 1, sizeof(char));
	if (!string)
		return (NULL);
	ft_strlcpy(string, s1, length + 1);
	while (*s2)
		string[length++] = *s2++;
	return (string);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	index;

	index = 0;
	while ((index + 1) < size && src[index])
	{
		dst[index] = src[index];
		index++;
	}
	if (size)
		dst[index] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}
