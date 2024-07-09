#include "../includes/minishell.h"

//if [ "$(./minishell 'echo hello')" = "hello" ]; then echo "Succes : le minishell renvoi bien 'hello'"; else echo "Echec : pas d'envoi de 'hello'"; fi

// TODO
// segfault avec double quote sur plusieurs '-n'
// echo -nnnnn "salut" : segfault

// echo -n : pas de retour a la ligne et chevauche le prompt
// ex : echo -n salut
// salutminishell>  : moche
/*
int ft_echo (char **split_line, t_cmd *cmd)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	if (split_line [1] && ft_strncmp(split_line[1], "-n", 2) == 0)
	{
		printf("ca n un peu\n");
		while (split_line[1][i++])
		{
			if (split_line[1][i] != 'n')
			{
				newline = false;
				break;
			}
		}
	}
	while (split_line[i])
	{
		if (split_line[i][0] == '>') //brute force pas ouf ?
		ft_putstr_fd(split_line[i], 1);
		i++;
		if (split_line[i])
			ft_putchar_fd(' ', 1);
	}
	if (newline == true)
			ft_putchar_fd('\n', 1);
	// ft_freetab(split_line);
	return (EXIT_SUCCESS);
}*/

int ft_echo(char **split_line, t_cmd *cmd)
{
    int i;
    bool newline;

    i = 1;
    newline = true;

    if (split_line[1] && strncmp(split_line[1], "-n", 2) == 0)
    {
        i++;
        newline = false;
    }

    while (split_line[i])
    {
        if (split_line[i][0] == '>')
            break;

        ft_putstr_fd(split_line[i], 1);
        i++;
        if (split_line[i])
            ft_putchar_fd(' ', 1);
    }

    if (newline == true)
        ft_putchar_fd('\n', 1);

    return (EXIT_SUCCESS);
}