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
. determination sans faille ---------------		: laubry
. idee irrealisable pour le commun des mortels		: amassias
*/



/*
TODO general

MAIN
- refactoriser la fonction main() et rendre l'integralite de l'executing modulaire

HEREDOC
- heredoc est le principal frein a la progression de l'executing, peut etre vaut-il mieux le gerer en dernier
- gerer ctrl + c dans le heredoc
- comprendre pourquoi heredoc ne recoit pas la commande entree par l'utilisateur (parsing ?)

REDIRECTION
- gerer le soucis des redirections qui sont gerees que dans un sens, mais encore une fois faut voir avec le parsing je pense
- quand tout sera OK, essayer de retirer le maximum de exit() que possible pour retourner a la racine du main autant que possible

VALGRIND
- fix autant de leak que possible avant de merge les deux parties
*/

static void process_input(char *line, t_cmd *cmd, t_token *token)
{
    if (line == NULL)
    {
        printf("CTRL + D from shell_loop\n");
        free_structs(cmd, token);
        exit(0); // Handle exit on EOF (CTRL + D)
    }

    if (*line)
        add_history(line);

    if (execute(line, cmd) == EXIT_COMMAND)
    {
        printf("FREE by EXIT COMMAND (shell_loop)\n");
        free_structs(cmd, token);
        free(line);
        exit(0); // Handle explicit exit command
    }
}

static int init_shell_exec(t_cmd **cmd, t_token **token, char **envp)
{
    if (malloc_structs(cmd, token) != 0)
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
    t_token *token;

    while (1)
    {
        if (init_shell_exec(&cmd, &token, envp) != 0)
            return;

        line = readline("MINISHELL>");
        process_input(line, cmd, token);
        cleanup(line, cmd, token);
    }
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    // Setup signal handlers
    signals();

    // Start shell loop
    shell_exec_loop(envp);

    return 0;
}

