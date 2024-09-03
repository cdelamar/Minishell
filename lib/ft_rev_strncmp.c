#include "libft.h"

int	ft_rev_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	while (len1 && len2 && n)
	{
		if (s1[len1 -1] != s2[len2 -1])
			return (s1[len1 -1] - s2[len2 -1]);
		len1--;
		len2--;
		n--;
	}
	if (n == 0)
		return (0);
	return (len1 - len2);
}