/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:38:07 by cdelamar          #+#    #+#             */
/*   Updated: 2024/06/14 21:56:29 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

size_t ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	int		size;
	int		i;
	char	*dest;

	size = 0;
	i = 0;
	while (s[size])
	{
		size++;
	}
	dest = (char *)malloc((size + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char *s, unsigned int start, size_t len)

{
	size_t	i;
	char	*str;

	i = 0;
	if (!s || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len && s[start])
		str[i++] = s[start++];
	str[len] = '\0';
	return (str);
}


static int	words_counter(char *s, char c)
{
	int	counter;

	counter = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			counter++;
		while (*s != c && *s)
			s++;
	}
	return (counter);
}

static size_t	get_word_size(char *s, char c)
{
	size_t	word_size;

	word_size = 0;
	while (*s == c && *s)
		s++;
	while (*s != c && *s)
	{
		word_size++;
		s++;
	}
	return (word_size);
}

char	**ft_split(char *s, char c)
{
	char	**res;
	int		i;
	int		words;
	size_t	word_size;

	i = 0;
	words = words_counter(s, c);
	res = (char **)malloc((words + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			word_size = get_word_size(s, c);
			res[i++] = ft_substr(s, 0, word_size);
			s += word_size;
		}
	}
	res[i] = NULL;
	return (res);
}