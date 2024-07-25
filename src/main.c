/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:06:47 by cdelamar          #+#    #+#             */
/*   Updated: 2024/07/25 00:41:01 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
TODO LELOUP

- virer les fonctions de 60 lignes pour les decouper proprements (pipe_execute et la call_builtins)
- fix 'export' qui segfault alors qu'avant ca allait
- fix 'echo' mais je vais avoir besoin du parsing donc je crois que je perd mon temps mais a voir si je peux pas faire un truc
- virer 'exit' du basic (le code est divise en 3 parties je vais te faire un dessin apres) et le mettre en builtin
- gerer ctrl + c dans le heredoc
- fixer le '|' qui vaut ctrl + D
- gerer le soucis des redirections qui sont gerees que dans un sens, mais encore une fois faut voir avec le parsing je pense
- quand tout sera OK, essayer de retirer le maximum de exit() que possible pour retourner a la racine du main autant que possible
*/


int main(int argc, char **argv, char **envp)
{
	char *line;
	t_cmd *cmd;
	t_ctx *ctx;
	t_token *token;

	(void)argc;
	(void)argv;

	// CTRL + C and CTRL + '\'
	signals();

	// SHELL LOOP
	while (1)
	{
		if (malloc_structs(&cmd, &ctx, &token) != 0)
		{
			ft_putendl_fd(MALLOC_FAILURE, 2);
			return (1);
		}
		cmd->env = envp;
		//if (ft_copy_envp(envp, cmd) == 1)
		//	return (EXIT_FAILURE);
		line = readline("MINISHELL>");

		// CTRL + D
		if (line == NULL)
		{
			free_structs(cmd, ctx, token);
			printf("CTRL + D\n");
			return (0);
		}

		// HISTORY LINE
		if (*line)
			add_history(line);

		// EXECUTING
		if (execute(line, cmd) == EXIT_COMMAND) // define OK ?
		{
			// modif de var_g
			printf("FREE by EXIT COMMAND (main.c line 72)\n");
			free_structs(cmd, ctx, token);
			free(line);
			return (0);
		}
		free_structs(cmd, ctx, token);
		free(line);
	}
	return (0);
}

