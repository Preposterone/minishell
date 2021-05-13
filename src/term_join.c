#include "minishell.h"

char	*ter(char *s2, int i)
{
	char	*r;
	int		len;

	len = en(s2);
	r = (char *)ft_calloc(len + 1, sizeof(char));
	if (!r)
		return (NULL);
	while (i < len && s2 != NULL && s2[++i] && s2[i] != '\0' && s2[i] != '\n')
	{
		r[i] = s2[i];
	}
	r[i] = '\0';
	return (r);
}

void	strj_lex_mas2(t_for_in_lexer *lex)
{
	if (lex->mas_line)
	{
		free((void **)lex->mas_line);
		lex->mas_line = NULL;
	}
}

char	**strjoin_lex_mas(int len, t_for_in_lexer *lex)
{
	char	**lin;
	int		i;

	i = 0;
	lex->len = len;
	lin = (char **)ft_calloc((len + 1), sizeof(char *));
	if (!lin)
		return (NULL);
	while (lex->mas_line && lex->mas_line != NULL
		&& lex->mas_line[i] && lex->mas_line[i] != NULL && i < len)
	{
		lin[i] = ter(lex->mas_line[i], -1);
		if (lex->mas_line[i])
		{
			lex->mas_line[i] = free_null(lex->mas_line[i]);
			free((void *)lex->mas_line[i]);
			lex->mas_line[i] = NULL;
		}
		i++;
	}
	lin[i++] = ter(lex->line, -1);
	lin[i] = NULL;
	strj_lex_mas2(lex);
	return (lin);
}

char	**strjoin_pr_mas(int len, char **s, char *line)
{
	char	**lin;
	int		i;

	i = 0;
	lin = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!lin)
		return (NULL);
	while (i < len - 1 && s && s != NULL && s[i] && s[i] != NULL)
	{
		lin[i] = ter(s[i], -1);
		if (s[i])
			s[i] = free_null(s[i]);
		i++;
		if (!s[i])
			break ;
	}
	lin[i++] = ter(line, -1);
	lin[i] = NULL;
	if (s)
	{
		free((void **)s);
		s = NULL;
	}
	return (lin);
}
