#include "../includes/minishell.h"

/*
REMINDER

readline, rl_clear_history,
rl_on_new_line		<<
rl_replace_line		<<
rl_redisplay		<<
add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs
*/

void handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0); // clear current input line
	rl_on_new_line();		// move curos to new line
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();			// "redisplay (?)" prompt / line buff
}