/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:12:40 by cdelamar          #+#    #+#             */
/*   Updated: 2023/10/27 11:54:30 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void    ft_abcdefg (unsigned int n, char *s)
{
	int	i;
	int	i;
	int	i;

		*s = 'a' + n;
}*/
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &(s[i]));
		i++;
	}
}
/*int main ()
{
		char tab[] = "testing test";
		printf("%s\n", tab);

		ft_striteri(tab, ft_abcdefg);
		printf("%s\n", tab);

		return (0);
}*/
