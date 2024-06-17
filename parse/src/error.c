#include "minishell.h"

//faire un enum si c plus beau pour clement
int	check_error(int code_error)
{
	if (code_error == ERROR_NODE)
		printf("node creation error");
	else if (code_error == ERROR_ARGS)
		printf("errer arguments");
	//else if (code_error == )
	//	printf("");
	return (0);
}
