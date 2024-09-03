/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:12:43 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 17:12:12 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	*st_strcat(char *dest, const char *src)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (dest[i])
// 		i++;
// 	while (src[j])
// 	{
// 		dest[i] = src[j];
// 		i++;
// 		j++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }
/*
static char	*st_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
*/
char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

// int	main(void)
// {
// 		char    tab1[] = "mais si, ";
// 		char    tab2[] = "ca marche";
// 		char    *tab_ft;

// 		tab_ft = ft_strjoin(tab1, tab2);
// 		printf("%s\n", tab_ft);

// 		free(tab_ft);
// 		return (0);
// }