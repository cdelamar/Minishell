/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:13:11 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 11:52:59 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	forward;
	size_t	backward;
	char	*str;

	str = 0;
	if (s1 != 0 && set != 0)
	{
		forward = 0;
		backward = ft_strlen(s1);
		while (s1[forward] && ft_strchr(set, s1[forward]))
			forward++;
		while (s1[backward - 1] && ft_strchr(set, s1[backward - 1])
			&& backward > forward)
			backward--;
		str = (char *)malloc(sizeof(char) * (backward - forward + 1));
		if (str)
			ft_strlcpy(str, &s1[forward], backward - forward + 1);
	}
	return (str);
}

/*
int	main(void)
{
	const char    tab[] = "   test, check, test       ";
	char    *tab_rest;

	tab_rest = ft_strtrim(tab);

	printf("%s\n", tab_rest);

	free(tab_rest);
	return (0);
}*/