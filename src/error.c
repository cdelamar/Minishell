#include "minishell.h"

//faire un enum si c plus beau pour clement
int	check_error(int code_error)
{
	if (code_error == ERROR_NODE)
		printf("node creation error");
	else if (code_error == ERROR_ARGS)
		printf("error arguments");
	else if (code_error == ERROR_QUOTE)
		printf("error solo quote detected");
	return (0);
}

int	check_error_before_split(char *line)
{
	int	i;
	int	dbl_quote;
	int	spl_quote;

	i = 0;
	dbl_quote = 0;
	spl_quote = 0;
	while(line[i])
	{
		if (line[i] == '"')
			dbl_quote += 1;
		else if (line[i] == '\'')
			spl_quote +=1;
		i++;
	}
	if (dbl_quote % 2 != 0 || spl_quote % 2 != 0)
		return (check_error(ERROR_QUOTE));
	return (1);
}
