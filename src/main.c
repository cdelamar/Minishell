/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:06:47 by cdelamar          #+#    #+#             */
/*   Updated: 2024/09/06 00:31:44 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO handle 'exit 0 | exit 1'

// memory :
// still reachable :    'ls | dqwdqwdqwd'
// still reachable :	'qdwdqwqdwqwd | ls"
// invalid read :       'wfekljfweljkljkwef'

// major :
// handle 'qwwqls | wc' : FIND OUT WHY PIPE DOESNT CHECK 1ST COMMAND

// minor :
// handle 'sort << "" '
// handle 'cat <test.txt'

#include "../includes/minishell.h"

volatile sig_atomic_t g_signal = 0;


// ??? faut free dans pipe exec cest sur

static void process_input(char *line, t_cmd *cmd)
{
    int ret;

    if (line == NULL)
    {
        //printf("CTRL + D from shell_loop\n");
        free_structs(cmd);
        exit(0); // Handle exit on EOF (CTRL + D)
    }

    if (space_only(line) == true)
    {
        free_structs(cmd);
        return;
    }

    if (*line)
        add_history(line);

    ret = execute(line,cmd); // execute retourne un int mais je men sert pas


    /* OBSOLETE COMMAND : MAY CONSIDER REMOVE / REUSE IT */
    // if (ret == EXIT_COMMAND)
    // {
    //     free_structs(cmd);
    //     free(line);
    //     exit(0);
    // }
    /* -------------------------------------------------*/
    /// YA UN MONDE ///
    // printf ("\n\n\n ************ RET == %d \n\n\n", ret);
    free_cmd(cmd);
    return;

    //// ALTERNATIVE DE : ////
    /*else if (ret == EXIT_SUCCESS || ret == EXIT_FAILURE)
    {
        printf("as if it will not decay and fail you\n\n");
        if (cmd->path_command)
            ft_freetab(cmd->path_command);
        if(cmd->path_split)
            ft_freetab(cmd->path_split);
        if (cmd)
            free(cmd);
    }*/
}

static int init_shell_exec(t_cmd **cmd, char **envp)
{
    if (malloc_structs(cmd) != 0)
    {
        ft_putendl_fd(MALLOC_FAILURE, 2);
        return 1;
    }
    (*cmd)->env = envp;
    (*cmd)->heredoc_processed = FALSE;
    return 0;
}

void shell_exec_loop(char **envp)
{
    char *line;
    t_cmd *cmd;

    while (1)
    {
        if (init_shell_exec(&cmd, envp) != 0)
        {
            printf("init return here\n");
            return;
        }
        line = readline("$ ");
        process_input(line, cmd);
        printf ("THE PROCESS RETURN \n\n");
        free(line); // LEAK
        printf("end of while1 loop\n\n\n");
    }
}

int main(int argc, char **argv, char **envp)
{
   // g_signal = 0;
    (void)argv;

    if (argc != 1)
    {
        printf("invalid argument.\n");
        return (0);
    }
    rl_outstream = stderr;

    signals();

    shell_exec_loop(envp);
    printf ("\n\n LEFT THE LOOP \n\n");
    return 0;
}

