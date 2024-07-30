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

									==== PROJET MINISHELL ====

ce projet consiste a realiser un simple shell basee majoritairement sur bash (bourne again shell).
Il s'agit d'un projet complexe, divisee en deux parties distincte dans la theorie, mais plus difficile
a dissocier dans la pratique:

- Le PARSING (par laubry) -
Consiste a diviser la chaine de charactere entree par l'utilisateur par categories (tokens)
pour pouvoir traiter l'information

- l'EXECUTING (par cdelamar) -
Traite les donnees 'parsees' pour les utiliser via diverses commandes

Par soucis de simplicite, de nombreux commentaires sont inscrits ici et la autour du code.
libre a vous d'utiliser 'search' (ctrl + alt + F) pour naviguer

										==== LEGENDE ====

+ WIP + (work in progess) : il s'agit de potentiel fonctions on ligne de code pas encore operationnels
ou desormais obsoletes, mais pas encore supprimees pour d'eventuels tests.

+ TODO + (to do) : liste de taches a effectuer

+ PISTE + Ces commentaires sont la pour etayer une potentielle reflexion sur l'architecture meme du code,
allant de la suggestion de nouvelles fonction a la refonte de celles - ci

- sans titre - : un descriptif simple de parties de code, ou de fonctions

										==== EXECUTING ====

A la maniere de Pipex (projet precedement realisee lors du cursus), l'executing permet de gerer les commandes
entrees par l'utilisateur et de les effectuer sous certaines conditions (redirections, arguments...)
Des builtins sont implementees, a savoir : 'echo', 'unset', 'pwd', 'export', 'cd', 'env' et 'exit'.

. auteurs du projet : cdelamar / laubry

-- aide et remerciements --
. expertise et debugage -------------------		: acasamit / cgodard
. conseils avisees ------------------------		: gprigent / maxborde / gschwartz
. idee irrealisable pour le commun des mortels 	: amassias
. determination sans faille ---------------		: laubry
*/



/*
TODO general

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
		cmd->heredoc_processed = FALSE;
		//if (ft_copy_envp(envp, cmd) == 1)
		//	return (EXIT_FAILURE);
		line = readline("MINISHELL>");

		// CTRL + D
		if (line == NULL)
		{
			free_structs(cmd, ctx, token);
			printf("CTRL + D from main.c (line 59)\n");
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

