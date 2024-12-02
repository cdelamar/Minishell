/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:13:19 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 11:52:45 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	else
		return (c);
}

/*int	main(void)
{
	char c = 'c';
	int res = ft_toupper((unsigned char) c);
	printf("%d\n", res);

	char c2 = 'c';
	int res2 = toupper((unsigned char) c);
	printf("%d\n", res2);

	return (0);


}*/