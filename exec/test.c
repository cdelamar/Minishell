/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelamar <cdelamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:26:29 by cdelamar          #+#    #+#             */
/*   Updated: 2024/06/13 17:43:40 by cdelamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

enum token_type {
	WORD, // command
	OPERATOR, // | < > etc..
	APPEND, // trunc
	HEREDOC, // probleme > lgalloux
	VAR, // $[un truc]
	ENV, // env
	REDIRECT, // <<
	DOUBLE_QUOTE
};

typedef struct s_token {    // "gcc" "./test.c" "|" "cat" "-e" >> echo ""ouais c'est greg""
	enum token_type type;
	char *value;
	struct s_token *next;
} t_token;

enum token_type lexer (char *value)
{
	if (strcmp(value, "|") == 0)
        return OPERATOR;
    else if (strcmp(value, ">>") == 0)
        return APPEND;
    else if (strcmp(value, "<<") == 0)
        return HEREDOC;
    else if (strcmp(value, ">") == 0 || strcmp(value, "<") == 0)
        return REDIRECT;
    else if (value[0] == '$')
        return VAR;
    else if (strcmp(value, "env") == 0)
        return ENV;
    else if (value[0] == '"')
        return DOUBLE_QUOTE;
    else
        return WORD;
}

t_token *create_token (char *value, enum token_type)
{
	    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->type = lexer(value);
    new_token->value = strdup(value);
    new_token->next = NULL;
    return new_token;
}

t_token *tokenizer(char *line)
{
	int i;
	char **list;
	enum token_type type;

	i = 0;
	list = ft_split(line, ' '); //"ls" "-l"
	while (list[i])
	{
		list[i] = create_token(list[i], type);
		// node create
		// node add_back
		i++;
	}

}

int main (int argc, char **argv, char **envp)
{
	char *line;

	line = readline("rsh>");
	//line = "ls -l"
	tokenizer(line);
	free (line);
	return (EXIT_SUCCESS);
}
