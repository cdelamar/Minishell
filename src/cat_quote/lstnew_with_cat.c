/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew_with_cat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laubry <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:43:00 by laubry            #+#    #+#             */
/*   Updated: 2024/08/14 16:56:02 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*concat_and_free(char *str1, char *str2, int *boul)
{
	char	*temp;

	*boul = 1;
	temp = ft_strjoin(str1, str2);
	free(str1);
	return (temp);
}

static void	left_concat(char **str, int i, int *modif)
{
	int		boul;
	char	*temp;

	boul = 0;
	if (!check_is_space_node(str, i -1) && !check_is_space_node(str, i)
		&& str[i -1] != NULL && str[i] != NULL)
	{
		if (str[i -1] == NULL)
			temp = str[i];
		else
			temp = concat_and_free(str[i -1] , str[i], &boul);
		str[i] = ft_strdup(temp);
		if (boul == 1)
		{
			free(str[i -1]);
			str[i -1] = NULL;
			str = mouve_str(str, i - 1);
		}
		free(temp);
		*modif = 1;
	}
}

static void	right_concat(char **str, int i, int *modif)
{
	int		boul;
	char	*temp;

	boul = 0;
	if (!check_is_space_node(str, i +1)
		&& !check_is_space_node(str, i) && str[i +1] != NULL)
	{
		if (str[i +1] == NULL)
			temp = str[i];
		else
			temp = concat_and_free(str[i], str[i +1], &boul);
		str[i] = ft_strdup(temp);
		if (boul)
		{
			free(str[i + 1]);
			str[i + 1] = NULL;
			str = mouve_str(str, i + 1);
		}
		free(temp);
		*modif = 1;
	}
}

int	lstnew_with_cat(char **str, int i)
{
	int		modif;

	modif = 0;
	if (i > 0)
		left_concat(str, i, &modif);	
	right_concat(str, i, &modif);
	return (modif);
}
