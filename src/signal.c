#include "../includes/minishell.h"

// CTRL + C interaction

void sigint_handler(int sig)
{
    if (sig == SIGINT)
	{
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