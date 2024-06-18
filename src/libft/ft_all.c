#include "minishell.h"

size_t ft_strlen(const char *str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

char *ft_substr(const char *s, unsigned int start, size_t len)
{
    char *substr = (char *)malloc((len + 1) * sizeof(char));
    if (!substr)
        return NULL;
    for (size_t i = 0; i < len; i++)
        substr[i] = s[start + i];
    substr[len] = '\0';
    return substr;
}
