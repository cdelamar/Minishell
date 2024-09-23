/* ************************************************************************** */


/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:27:10 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/25 10:36:34 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
    {
        int exit_code = ft_exit(split_line, cmd);
        if (cmd->pid1 == 0)
        {
            ft_freetab(split_line);
            free(cmd);
            restore_fd(saved_in, saved_out); //fd test
            exit(exit_code);
        }
        ret = exit_code;
    }
    restore_fd(saved_in, saved_out);
    return (ret);
}

static int redirect_manager(char **split_line, int saved_stdin, int saved_stdout, t_cmd *cmd)
{
    if (handle_redirections(split_line, 0, cmd) == EXIT_FAILURE)
	{
        restore_fd(saved_stdin, saved_stdout);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static int backup_manager(char **split_line, int *saved_stdin, int *saved_stdout, t_cmd *cmd)
{

    (void)split_line;
    if (backup_fd(saved_stdin, saved_stdout) < 0)
        return EXIT_FAILURE;

    if (redirect_manager(split_line, *saved_stdin, *saved_stdout, cmd) == EXIT_FAILURE)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int ft_builtin(char *line, t_cmd *cmd)
{
	char **split_line;
	int saved_in;
	int saved_out;
	int ret;

	split_line = ft_split(line, ' ');
	if (!split_line)
		return EXIT_FAILURE;

	if (backup_manager(split_line, &saved_in, &saved_out, cmd) == EXIT_SUCCESS)
		ret = builtin_commands(split_line, cmd, saved_in, saved_out);
	else
		ret = EXIT_FAILURE;
	ft_freetab(split_line);
	return ret;
}

