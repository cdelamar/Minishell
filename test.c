int	is_quote(char *s, int i)
{
	char	c;

	c = '\0';
	if (s[i] == '"')
		c = '"';
	else if (s[i] == '\'')
		c = '\'';
	i++;
	while (s[i] != c && s[i])
		i++;
	if (s[i] == '\0')
		return (0);
	i++;
	return (i);
}

size_t	count_word(char *s)
{
	size_t	word;
	int		i;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (!is_char(s[i]))
		{
			if (s[i] == '\0')
				return (0);
			if (s[i] == ' ')
			{
				while (s[i] == ' ' && s[i])
					i++;
			}
			else if (s[i] == '"' || s[i] == '\'')
			{
				i = is_quote(s, i);	
				word++;
			}
			else if (s[i] == '|' || s[i] == '>' || s[i] == '<')
			{
				word++;
				i++;
			}
		}
		else if (ft_isalpha(s[i]))
		{
			while (ft_isalpha(s[i]))
				i++;
			word++;
		}
	}
	return (word);
}

