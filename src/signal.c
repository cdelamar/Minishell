/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:01:33 by cdelamar          #+#    #+#             */
/*   Updated: 2024/08/07 17:18:19 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// CTRL + C interaction

// TODO handle exit codes

/*

    SIGINT (Interrupt Signal)
        Exit Code: 130
        Description: Indicates that the process was terminated by a SIGINT, which is typically triggered by pressing CTRL+C.
        #define: SIGINT (Standard in <signal.h>)

    SIGQUIT (Quit Signal)
        Exit Code: 131
        Description: Indicates that the process was terminated by a SIGQUIT, which is often triggered by CTRL+\.
        #define: SIGQUIT (Standard in <signal.h>)

    SIGTERM (Termination Signal)
        Exit Code: 143
        Description: Indicates that the process was terminated by a SIGTERM, a signal used to request a program to stop running.
        #define: SIGTERM (Standard in <signal.h>)

    SIGHUP (Hangup Signal)
        Exit Code: 129
        Description: Indicates that the process was terminated by a SIGHUP, which typically occurs when the controlling terminal is closed.
        #define: SIGHUP (Standard in <signal.h>)

    SIGKILL (Kill Signal)
        Exit Code: 137
        Description: Indicates that the process was terminated by a SIGKILL, which cannot be caught or ignored.
        #define: SIGKILL (Standard in <signal.h>)

    SIGSEGV (Segmentation Fault)
        Exit Code: 139
        Description: Indicates that the process was terminated due to a segmentation fault.
        #define: SIGSEGV (Standard in <signal.h>)

    SIGPIPE (Broken Pipe)
        Exit Code: 141
        Description: Indicates that the process was terminated due to writing to a pipe with no readers.
        #define: SIGPIPE (Standard in <signal.h>)

    SIGALRM (Alarm Clock)
        Exit Code: 142
        Description: Indicates that the process was terminated by an alarm clock signal (SIGALRM), often used for timers.
        #define: SIGALRM (Standard in <signal.h>)

Additional Considerations

    Normal Exit (0): Indicates successful completion of a process. This is not related to a signal but should be handled in any shell.
    Error Exit (1 or other): Indicates an error or unsuccessful execution. Custom error codes can also be used depending on the specific needs of your shell.

*/

extern int g_signal;

void sigint_handler(int sig)
{
    if (sig == SIGINT)
	{
        g_signal = 1;
        rl_replace_line("", 0);
        printf("\n");
        rl_on_new_line();
        rl_redisplay();
    }
}

void	signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN); // CTRL + \ interaction
}