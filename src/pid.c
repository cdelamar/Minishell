
#include "../includes/minishell.h"

// WIP : trying to make a more modular version of the basic execute, for 50 lines seems a bit much

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

int handle_child_process(char *line, t_cmd *cmd)
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
    printf("incorrect inputs : pid. (line 50)\n");
    ft_freetab(split_line);
    return EXIT_FAILURE;
}

int handle_parent_process(pid_t pid, char **split_line)
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


/*
int handle_child_process(char *line, t_cmd *cmd) {
    char **split_line = ft_split(line, ' ');

    if (handle_redirections(split_line) < 0) {
        printf("ERROR (exec.c line 117)\n");
        ft_freetab(split_line);
        return EXIT_FAILURE;
    }

    char *command = cmd_finder(split_line, cmd);
    if (command) {
        execve(command, split_line, cmd->env);
    }
    printf("incorrect inputs : exec.c (line 123)\n");
    ft_freetab(split_line);
    return EXIT_FAILURE;
}

int handle_parent_process(t_cmd *cmd) {
    int status;
    if (waitpid(cmd->pid1, &status, 0) == -1) {
        printf("waitpid error (exec.c line 146)\n");
        return EXIT_FAILURE;
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE) {
        printf("child process failed (exec.c line 152)\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}*/