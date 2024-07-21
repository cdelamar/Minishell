/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:27:10 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/18 13:51:15 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO : FIX FT_EXPORT
// TODO : fix segfault when 'man echo 3' then 'q'

/*
int	ft_builtin(char *line, t_cmd *cmd)
{
    char	**split_line;
    int     saved_stdin;
    int     saved_stdout;

    split_line = ft_split(line, ' ');
    if (backup_fd(&saved_stdin, &saved_stdout) < 0)
    {
        ft_freetab(split_line);
        return (EXIT_FAILURE);
    }

    if (handle_redirections(split_line) == EXIT_FAILURE)
    {
        restore_fd(saved_stdin, saved_stdout);
        ft_freetab(split_line);
        return (EXIT_FAILURE);
    }

    if (ft_strcmp(split_line[0], "unset") == 0)
        return (ft_unset(split_line, cmd));
    else if (ft_strcmp(split_line[0], "echo") == 0)
    {
        int ret = ft_echo(split_line);
        restore_fd(saved_stdin, saved_stdout);
        ft_freetab(split_line);
        return ret;
    }
    else if (ft_strcmp(split_line[0], "cd") == 0)
    {
        int ret = ft_cd(split_line[1]);
        restore_fd(saved_stdin, saved_stdout);
        ft_freetab(split_line);
        return ret;
    }
    else if (ft_strcmp(split_line[0], "export") == 0)
    {
        int ret = ft_export(split_line, cmd);
        restore_fd(saved_stdin, saved_stdout);
        ft_freetab(split_line);
        return ret;
    }
    else if (ft_strcmp(line, "env") == 0)
    {
        ft_freetab(split_line);
        int ret = ft_env(cmd);
        restore_fd(saved_stdin, saved_stdout);
        return ret;
    }
    else if (ft_strcmp(line, "pwd") == 0)
    {
        ft_freetab(split_line);
        int ret = ft_pwd();
        restore_fd(saved_stdin, saved_stdout);
        return ret;
    }

    // WIP
    else if (ft_strcmp(line, "exit") == 0)
    {
        ft_freetab(split_line);
        return (EXIT_SUCCESS);
    }

    restore_fd(saved_stdin, saved_stdout);
    ft_freetab(split_line);
    return (EXIT_FAILURE);
}*/


static int builtin_commands(char **split_line, t_cmd *cmd, int saved_in, int saved_out)
{
    int ret;

	ret = EXIT_FAILURE;
    if (ft_strcmp(split_line[0], "unset") == 0)
        ret = ft_unset(split_line, cmd);
    else if (ft_strcmp(split_line[0], "echo") == 0)
        ret = ft_echo(split_line);
    else if (ft_strcmp(split_line[0], "cd") == 0)
        ret = ft_cd(split_line[1]);
    else if (ft_strcmp(split_line[0], "export") == 0)
        ret = ft_export(split_line, cmd);
    else if (ft_strcmp(split_line[0], "env") == 0)
        ret = ft_env(cmd);
    else if (ft_strcmp(split_line[0], "pwd") == 0)
        ret = ft_pwd();
    else if (ft_strcmp(split_line[0], "exit") == 0)
        ret = EXIT_SUCCESS;

    restore_fd(saved_in, saved_out);
    return (ret);
}

static int redirect_manager(char **split_line, int saved_stdin, int saved_stdout)
{
    if (handle_redirections(split_line) == EXIT_FAILURE)
	{
        restore_fd(saved_stdin, saved_stdout);
        ft_freetab(split_line);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static int backup_manager(char **split_line, int *saved_stdin, int *saved_stdout)
{
    if (backup_fd(saved_stdin, saved_stdout) < 0)
	{
        ft_freetab(split_line);
        return EXIT_FAILURE;
    }

    if (redirect_manager(split_line, *saved_stdin, *saved_stdout) == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int ft_builtin(char *line, t_cmd *cmd)
{
    char **split_line;
    int saved_in;
	int	saved_out;
    int ret;

	ret = EXIT_FAILURE;
    split_line = ft_split(line, ' ');

	if (backup_manager(split_line, &saved_in, &saved_out) == EXIT_SUCCESS)
		ret = builtin_commands(split_line, cmd, saved_in, saved_out);

	printf("should i stay\n");
    ft_freetab(split_line); // TODO : this function occur a segfault when 'cat < wrong_input' but why
	printf("should i go\n");
    return (ret);
}

/*
int	ft_builtin(char *line, t_cmd *cmd)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (handle_redirections(split_line) == EXIT_FAILURE)
	{
		ft_freetab(split_line);
		return (EXIT_FAILURE);
	}
	if (ft_strcmp(split_line[0], "unset") == 0)
		return (ft_unset(split_line, cmd));
	else if (ft_strcmp(split_line[0], "echo") == 0)
		return (ft_echo(split_line));
	else if (ft_strcmp(split_line[0], "cd") == 0)
		return (ft_cd(split_line[1]));
	else if (ft_strcmp(split_line[0], "export") == 0)
		return (ft_export(split_line, cmd));
	else if (ft_strcmp(line, "env") == 0)
	{
		ft_freetab (split_line);
		return (ft_env(cmd));
	}
	else if (ft_strcmp(line, "pwd") == 0)
	{
		ft_freetab (split_line);
		return (ft_pwd());
	}
	ft_freetab (split_line);
	return (EXIT_FAILURE);
}
*/