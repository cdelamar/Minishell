/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:25:42 by cdelamar          #+#    #+#             */
/*   Updated: 2024/11/22 18:25:43 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin_path(char *path, char *cmd)
{
	char	*full_path;
	int		path_len;
	int		cmd_len;

	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	full_path = malloc(path_len + cmd_len + 2);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, path);
	full_path[path_len] = '/';
	ft_strcpy(full_path + path_len + 1, cmd);
	return (full_path);
}

char	*find_path_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*handle_absolute_path(char *cmd_name)
{
	if (is_executable(cmd_name))
		return (strdup(cmd_name));
	return (NULL);
}

char	*search_in_path_dirs(char **path_dirs, char *cmd_name)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		cmd_path = ft_strjoin_path(path_dirs[i], cmd_name);
		if (cmd_path && is_executable(cmd_path))
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd_name, char **env)
{
	char	*path_env;
	char	*cmd_path;
	char	**path_dirs;

	if (cmd_name[0] == '/' || cmd_name[0] == '.')
		return (handle_absolute_path(cmd_name));
	path_env = find_path_env(env);
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
		return (NULL);
	cmd_path = search_in_path_dirs(path_dirs, cmd_name);
	ft_freetab(path_dirs);
	return (cmd_path);
}
