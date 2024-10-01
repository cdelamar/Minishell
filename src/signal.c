/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:01:33 by cdelamar          #+#    #+#             */
/*   Updated: 2024/10/01 19:31:26 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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



/*

    0: Success—Indicates that the command or program executed successfully without any errors.
    1: General Error—A catch-all exit code for a variety of general errors. Often used when the command or program encounters an error, but no specific exit code is available for the situation.
    2: Misuse of shell built-ins—Indicates incorrect usage of shell built-in commands or misuse of shell syntax.
    126: Command cannot execute—The command was found, but it could not be executed, possibly due to insufficient permissions or other issues.
    127: Command not found—The command was not found in the system's PATH, indicating that either the command does not exist or the PATH variable is incorrectly set.
    128: Invalid exit argument—Returned when a script exits with an invalid argument. This usually indicates an error in the script itself.
    128 + N: Fatal error signal N—Indicates that the command or program was terminated by a fatal error signal. For example, an exit code of 137 (128 + 9) means that the command was terminated by a SIGKILL signal.
    130: Script terminated by Control-C—Indicates that the command or script was terminated by the user using Control-C (SIGINT signal).
    255: Exit status out of range—Returned when the exit status is outside the valid range (0 to 254).

*/

extern sig_atomic_t g_signal;

// MAIN SIGNAL

void sigint_heredoc(int sig)
{
    if (sig == SIGINT)
    {
        g_signal = 1;
        // Close stdin to break readline
        close(STDIN_FILENO);
    }
}

void sigint_handler(int sig)
{
    if (sig == SIGINT)
	{
        g_signal = 1;
        //printf ("appel de signal\n");
        rl_replace_line("", 0);
        printf("\n");
        rl_on_new_line();
        rl_redisplay();
    }
}

void    heredoc_signals(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN); // CTRL + \ interaction

}

void setup_signal_handler(int signum, void (*handler)(int))
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; // Automatically restart interrupted system calls
    sigaction(signum, &sa, NULL);
}

void signals(void)
{
    setup_signal_handler(SIGINT, sigint_handler);
    setup_signal_handler(SIGQUIT, SIG_IGN); // Ignore CTRL+'\'
    setup_signal_handler(SIGPIPE, SIG_IGN);
}

void reset_signals(void)
{
    setup_signal_handler(SIGINT, SIG_DFL);
    setup_signal_handler(SIGQUIT, SIG_DFL);
}


/*
void sigint_handler(int sig)
{
    if (sig == SIGINT)
	{
        g_signal = 1;
        //printf ("appel de signal\n");
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

// HEREDOC SIGNAL

void sigint_heredoc(int sig)
{
    if (sig == SIGINT)
    {
        g_signal = 1;
        printf("\n");
    }
}

void    heredoc_signals(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN); // CTRL + \ interaction

}

// RESET SIGNAL

void    reset_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL); // DFL ????
}*/