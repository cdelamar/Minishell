#include "../includes/minishell.h"

// check man fork
// when pid < 0				: error
// when pid == 0			: child process
// else pid == child's ID	: parent process

// TODO : refactoring a more readable 'cmd_cat'
static char *cmd_cat(const char *path_split, char *slash, char *command)
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

static char *cmd_finder(char **split_line, t_cmd *cmd)
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

int basic_execute (char *line, t_cmd *cmd)
{
	char	*command;
	char	**split_line;
	int		i;

	i = 0;
	// exit_handler
	if (strcmp(line, "exit") == 0)
		return(EXIT_COMMAND);

	ft_path(cmd);
	cmd->pid1 = fork();
	//  error fork
	if (cmd->pid1 < 0)
		return (1);
	// child fork
	else if (cmd->pid1 == 0)
	{
		split_line = ft_split(line, ' ');
		command = cmd_finder(split_line, cmd);
		if(command)
			execve(command, split_line, cmd->env);
		free(split_line);
		return (1); // error
	}
	// parent fork
	else
		sleep(1);
	return (0);
}