#include "../includes/minishell.h"

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
/*
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

}*/