/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:04:41 by laubry            #+#    #+#             */
/*   Updated: 2023/11/29 23:04:18 by Laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_and_free_s1(char *s1, char *buffer)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (ft_strlen_char(s1, '\n')
				+ ft_strlen_char(buffer, '\n') + 2));
	if (dest != NULL)
	{
		while (s1 && s1[i] != '\0')
		{
			dest[i] = s1[i];
			i++;
		}
		while (buffer && buffer[j] && buffer[j] != '\n')
		{
			dest[i + j] = buffer[j];
			j++;
		}
		dest[i + j] = '\n';
		j += (buffer[j] == '\n');
		dest[i + j] = '\0';
	}
	return (ft_strjoin_and_free_s1_2(s1, dest));
}

int	ft_chr_line(char *buffer)
{
	int	i;

	i = 0;
	if (buffer == NULL)
		return (1);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		return (0);
	return (1);
}

void	ft_cut_buff(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i] != '\0')
	{
		buffer[j] = buffer[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	int			bytes_read;
	char		*dest;

	bytes_read = 1;
	dest = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (ft_chr_line(buffer) == 0)
	{
		ft_cut_buff(buffer);
		dest = ft_strjoin_and_free_s1(dest, buffer);
	}
	while (bytes_read > 0 && ft_chr_line(buffer) == 1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		else if (bytes_read == 0)
			return (dest);
		buffer[bytes_read] = '\0';
		dest = ft_strjoin_and_free_s1(dest, buffer);
	}
	return (dest);
}
/*a fonction ft_chr_line indique qu'il n'y a pas de ligne complète 
dans le tampon, la fonction ft_cut_buff est appelée pour 
supprimer la partie de la ligne présente dans le tampon, 
et le contenu du tampon est ajouté à dest en utilisant
 ft_strjoin_and_free_s1.*/

/* si c -1 return null et free tout
 si c 0 return dest

if (bytes_read < 0)
		{
			free(dest);
			return (-1);
		}
		if (bytes_read == 0)
		{
			free(dest);
			dest = NULL;
			return (0)
		}

*/