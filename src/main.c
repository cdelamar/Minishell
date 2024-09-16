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

#include "../includes/minishell.h"

volatile sig_atomic_t g_signal = 0;

static void process_input(char *line, t_cmd *cmd)
{
    if (line == NULL)
    {
        //printf("CTRL + D from shell_loop\n");
        free_structs(cmd);
        exit(0); // Handle exit on EOF (CTRL + D)
    }

    if (*line)
        add_history(line);

    if (execute(line, cmd) == EXIT_COMMAND)
    {
        //printf("FREE by EXIT COMMAND (shell_loop)\n");
        free_structs(cmd);
        free(line);
        exit(0); // Handle explicit exit command
    }
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
            return;
        line = readline("$ ");
        process_input(line, cmd);
        free_structs(cmd);  // LEAK : this free is necessary to avoid leaks but occurs segfaults in rare cases
                            // check minishell tester > 'mstester m'

        //cleanup(line, cmd);
    }
}

int main(int argc, char **argv, char **envp)
{
   // g_signal = 0;
    (void)argv;

    if (argc != 1)
    {
        printf("MiniSnail is supposed to work by typing './minishell'\n");
        return (0);
    }
    rl_outstream = stderr;
    // Setup signal handlers
    signals();

    // Start shell loop
    shell_exec_loop(envp);

    return 0;
}

