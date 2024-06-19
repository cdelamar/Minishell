#include "../includes/minishell.h"

char *cmd_cat(const char *path_split, char *slash, char *command)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;
	char	*res;

	s1_len = ft_strlen(path_split);
	s2_len = ft_strlen(slash);
	s3_len = ft_strlen(command);
	res = malloc((s1_len + s2_len + s3_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, path_split, s1_len + 1);
	ft_strlcat(res, slash, s1_len + s2_len + 1);
	ft_strlcat(res, command, ft_strlen(res) + s3_len + 1);
	return (res);
}

char *cmd_finder(char **split_line, t_cmd *cmd)
{
	int		i;
	char	*command;

	i = 0;

	while (cmd->path_split[i])
	{
		command = cmd_cat(cmd->path_split[i], "/", split_line[0]);
		if (access (command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}