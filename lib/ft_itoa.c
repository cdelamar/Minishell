/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:12:02 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 11:56:13 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_digits(int n)
{
	int	result;

	result = 1;
	if (n < 0)
	{
		result++;
		n = -n;
	}
	while (n >= 10)
	{
		result++;
		n /= 10;
	}
	return (result);
}

static char	*str_filler(char *str, int number_digits, int n)
{
	int	i;

	i = number_digits - 1;
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
		while (i > 0)
		{
			str[i] = '0' + (n % 10);
			i--;
			n /= 10;
		}
	}
	else
	{
		while (i >= 0)
		{
			str[i] = '0' + (n % 10);
			i--;
			n /= 10;
		}
	}
	str[number_digits] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		number_digits;

	number_digits = nb_digits(n);
	if (n == -2147483648)
	{
		return (ft_strdup("-2147483648"));
	}
	str = (char *)malloc((number_digits + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str_filler(str, number_digits, n);
	return (str);
}

//---------------  MAIN ------------
/*
int	main(void)
{
	int n = -2147483648;
	char *res = ft_itoa(n);

	printf("%s\n", res);
	free(res);
	return (0);
}*/