#include "libft.h"

char	*ft_strtok(char *str, const char delim)
{
	static char		*stock = NULL;
	char			*ptr;
	int				flg;

	flg = 0;
	ptr = NULL;
	if (str != NULL)
		stock = ft_strdup(str);
	while (*stock != '\0')
	{
		if (flg == 0 && *stock != delim)
		{
			flg = 1;
			ptr = stock;
		}
		else if (flg == 1 && *stock == delim)
		{
			*stock = '\0';
			stock += 1;
			break ;
		}
		stock += 1;
	}
	return (ptr);
}