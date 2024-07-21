
#include "../includes/minishell.h"

// WIP : trying to make a more modular version of the basic execute, for 50 lines seems a bit much


// handle_path obsolete ? (no more called in any functions for now)
int handle_path(t_cmd *cmd)
{
    ft_path(cmd);
    if (!cmd->path)
    {
        printf("command not found\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

// TODO put exit in builtins caller
int handle_exit_command(char *line)
{
    if (strcmp(line, "exit") == 0)
        return EXIT_COMMAND;
    return 0;
}

int set_command_path(t_cmd *cmd)
{
    ft_path(cmd);
    if (!cmd->path)
    {
        printf("command not found\n");
        return EXIT_FAILURE;
    }
    return 0;
}

int basic_child_process(char *line, t_cmd *cmd)
{
    char **split_line;
    char *command;

    split_line = ft_split(line, ' ');
    if (handle_redirections(split_line) < 0)
    {
        printf("ERROR (pid.c line 43)\n");
        return EXIT_FAILURE;
    }
    command = cmd_finder(split_line, cmd);
    if (command)
        execve(command, split_line, cmd->env);
    printf("incorrect inputs : pid.c (line 50)\n");
    ft_freetab(split_line);
    return EXIT_FAILURE;
}

int basic_parent_process(pid_t pid, char **split_line)
{
    int status;

    if (waitpid(pid, &status, 0) == -1)
    {
        printf("freetab (exec.c line 146)\n");
        ft_freetab(split_line);
        return EXIT_FAILURE;
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
    {
        printf("freetab (exec.c line 152)\n");
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
    exit_code = handle_exit_command(line);
    if (exit_code != 0)
        return exit_code;
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

