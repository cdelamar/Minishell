
#include "../includes/minishell.h"

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


// PISTE : basic_child se repose sur les redirections pour
// parser les potentiels chevron (<, << , >>, >) de redirection
// la gestion du status (2eme arg du handle_redirection) est primordiale
// pour pouvoir gerer heredoc differement des autres redirections.

// Dans le cas de 'basic_child_process', seul 'HEREDOC_ON' fait office
// de condition implementee. Il faudrait sans doute effectuer une
// condition pour 'HEREDOC_OFF', au cas ou.

int basic_child_process(char *line, t_cmd *cmd)
{
    char **split_line;
    char *command;

    // printf ("** basic child **\n");
    split_line = ft_split(line, ' ');
    if (handle_redirections(split_line, HEREDOC_ON, cmd) != 0)
    {
        printf("ERROR (basic_exec.c line 25)\n");
        ft_freetab(split_line);
        return EXIT_FAILURE;
    }
    // printf ("** handle_redirections = %d **\n", handle_redirections(split_line, 1, cmd));
    command = cmd_finder(split_line, cmd);
    if (command)
        execve(command, split_line, cmd->env);
    printf("command not found: %s\n", line);
    ft_freetab(split_line);
    return EXIT_FAILURE;
}


// surement le process parent qui fout la merde
int basic_parent_process(pid_t pid, char **split_line)
{
    int status;

    // printf ("** basic parent **\n");
    // printf("split line [0] = %s\n", split_line[0]);
    // printf("split line [1] = %s\n", split_line[1]);
    // printf("split line [2] = %s\n", split_line[2]);
    if (waitpid(pid, &status, 0) == -1)
    {
        // printf("freetab (basic_exec.c line 44)\n");
        // printf("** waitpid = -1 **\n");
        if (split_line)
            ft_freetab(split_line);
        return EXIT_FAILURE;
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
    {
        // printf("freetab (basic_exec.c line 50)\n");
        // printf("** le truc avec WIFEXITED **\n");
        if (split_line)
            ft_freetab(split_line);
        return EXIT_FAILURE;
    }
    // printf ("** basic parent succeed **\n");
    return EXIT_SUCCESS;
}

int basic_execute(char *line, t_cmd *cmd)
{
    int exit_code;
    char **split_line = NULL;

    split_line = ft_split(line, ' ');
    // printf ("** basic_execute **\n");
    // Handle exit command
   // exit_code = handle_exit_command(line);
   // if (exit_code == EXIT_COMMAND)
    //    return (EXIT_COMMAND);
    exit_code = set_command_path(cmd);
    if (exit_code != EXIT_SUCCESS)
        return exit_code;
    cmd->pid1 = fork();
    if (cmd->pid1 < 0)
        return EXIT_FAILURE; //Error forking
    else if (cmd->pid1 == 0)
	{
        exit_code = basic_child_process(line, cmd);
        // exit(exit_code); //Ensure the child process exits after handling
        return(exit_code); //Ensure the child process exits after handling
    }
	else
        return basic_parent_process(cmd->pid1, split_line);
    return EXIT_SUCCESS;
}
