/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:40:02 by cdelamar          #+#    #+#             */
/*   Updated: 2024/04/24 22:40:03 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freetab(char **tab)
{
	size_t i;
	i = 0;

	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
/*
void ft_freetab(char **tab)
{
    int i;

    if (!tab)
        return;
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        tab[i] = NULL;  // Ensure pointers inside tab are NULL'd after freeing
        i++;
    }
    free(tab);
    tab = NULL;  // Ensure the main pointer is NULL'd after freeing
}*/