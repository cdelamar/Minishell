
#include "../includes/minishell.h"

// TODO put exit in builtins caller

int set_command_path(t_cmd *cmd)
{
    ft_path(cmd);
    if (!cmd->path)
    {
        printf("command not found\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int basic_child_process(char *line, t_cmd *cmd) {
    char **split_line;
    char *command;

    split_line = ft_split(line, ' ');
    if (!split_line) {
        printf("ERROR: ft_split failed (basic_exec.c line 34)\n");
        return EXIT_FAILURE;
    }
    if (handle_redirections(split_line) < 0) {
        printf("ERROR (pid.c line 43)\n");
        ft_freetab(split_line);
        return EXIT_FAILURE;
    }
    command = cmd_finder(split_line, cmd);
    if (command)
        execve(command, split_line, cmd->env);
    printf("command not found: %s\n", line);
    ft_freetab(split_line);
    return EXIT_FAILURE;
}

int basic_parent_process(pid_t pid, char **split_line) {
    int status;

    if (waitpid(pid, &status, 0) == -1) {
        printf("freetab (basic_exec.c line 48)\n");
        if (split_line)
            ft_freetab(split_line);
        return EXIT_FAILURE;
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE) {
        printf("freetab (basic_exec.c line 54)\n");
        if (split_line)
            ft_freetab(split_line);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int basic_execute(char *line, t_cmd *cmd)
{
    int exit_code;
    char **split_line = NULL;

    // Handle exit command
   // exit_code = handle_exit_command(line);
   // if (exit_code == EXIT_COMMAND)
    //    return (EXIT_COMMAND);
    exit_code = set_command_path(cmd);
    if (exit_code != 0) {
        return exit_code;
    }
    cmd->pid1 = fork();
    if (cmd->pid1 < 0)
        return EXIT_FAILURE; // Error forking
    else if (cmd->pid1 == 0)
	{
        exit_code = basic_child_process(line, cmd);
        exit(exit_code); // Ensure the child process exits after handling
    }
	else
        return basic_parent_process(cmd->pid1, split_line);
    return EXIT_SUCCESS;
}

