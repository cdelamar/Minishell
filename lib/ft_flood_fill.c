/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flood_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:46:43 by laubry            #+#    #+#             */
/*   Updated: 2024/11/22 21:47:22 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_fill(char **tab, t_point size, t_point pos, char to_fill)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= size.x || pos.y >= size.y
		|| tab[pos.y][pos.x] != to_fill)
		return ;
	else
		tab[pos.y][pos.x] = 'F';
	ft_fill(tab, size, (t_point){pos.x + 1, pos.y}, to_fill);
	ft_fill(tab, size, (t_point){pos.x - 1, pos.y}, to_fill);
	ft_fill(tab, size, (t_point){pos.x, pos.y + 1}, to_fill);
	ft_fill(tab, size, (t_point){pos.x, pos.y - 1}, to_fill);
}

void	ft_flood_fill(char **tab, t_point size, t_point begin)
{
	ft_fill(tab, size, begin, tab[begin.y][begin.x]);
}
