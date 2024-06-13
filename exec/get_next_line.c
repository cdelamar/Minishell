/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:49:08 by cdelamar          #+#    #+#             */
/*   Updated: 2024/06/13 16:43:32 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*storage;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = ft_readline(fd, storage);
	if (!storage)
		return (NULL);
	line = ft_getline(storage);
	storage = ft_trim_storage(storage);
	return (line);
}

char	*ft_trim_storage(char *storage)
{
	size_t	index;
	size_t	i;
	char	*trimmed;

	index = 0;
	i = 0;
	while (storage[index] != '\n' && storage[index])
		index++;
	if (storage[index] == '\0')
	{
		free(storage);
		return (NULL);
	}
	trimmed = ft_calloc(ft_strlen(storage) - index + 1, sizeof(char));
	index++;
	while (storage[index])
		trimmed[i++] = storage[index++];
	free(storage);
	return (trimmed);
}

char	*ft_getline(char *storage)
{
	char	*line;
	size_t	index;
	size_t	i;

	index = 0;
	i = 0;
	if (!storage[index])
		return (NULL);
	while (storage[index] != '\n' && storage[index])
		index++;
	line = ft_calloc(index + 2, sizeof(char));
	index = 0;
	while (storage[index] != '\n' && storage[index])
		line[i++] = storage[index++];
	if (storage[index] == '\n')
		line[i] = '\n';
	return (line);
}

char	*ft_readline(int fd, char *storage)
{
	char		*storage_buffer;
	char		*buffer_to_read;
	int			bytes_read;

	if (!storage)
		storage = ft_calloc(1, sizeof(char));
	storage_buffer = storage;
	buffer_to_read = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (!ft_strchr(storage, '\n') && bytes_read >= 1)
	{
		bytes_read = read(fd, buffer_to_read, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer_to_read);
			free(storage_buffer);
			return (NULL);
		}
		buffer_to_read[bytes_read] = '\0';
		storage_buffer = storage;
		storage = ft_strjoin(storage_buffer, buffer_to_read);
		free(storage_buffer);
	}
	free(buffer_to_read);
	return (storage);
}
