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