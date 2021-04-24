#include "minishell.h"


char	*term_strjoin_n(char *s2, char *r, int i)
{
	r = (char *)malloc(sizeof(char) * (term_strlen(s2) + 1));
	if (!r)
		return (NULL);
	i = -1;
	while (s2[++i] && s2[i] != '\n')
		r[i] = s2[i];
	r[i] = '\0';
	return (r);
}

char	*term_strjoin(char *s1, char *s2)
{
	char			*r;
	unsigned int	i;
	unsigned int	j;

	if ((!s1 || s1 == NULL) && !s2)
		return (NULL);
	i = 0;
	r = NULL;
	if (!s1 || s1 == NULL)
		return (term_strjoin_n(s2, r, i));
	r = (char *)malloc(sizeof(char) * (term_strlen(s1) + term_strlen(s2) + 1));
	if (!r)
		return (NULL);
	while (s1[i] && s1[i] != '\n')
	{
		r[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2[++j] && s2[i] != '\n')
		r[i++] = s2[j];
	r[i] = '\0';
	if (s1 && s1 != NULL)
		free(s1);
	return (r);
}

char	*str_delet_last_char(char *s1)
{
	char			*r;
	unsigned int	i;

	if (!s1 && strlen(s1) == 1)
		return (NULL);
	r = (char *)malloc(sizeof(char) * (strlen(s1)));
	if (!r)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i + 1] && i < strlen(s1) - 1)
	{
		r[i] = s1[i];
		i++;
	}
	r[i] = '\0';
	if (s1)
	{
		free((void *)s1);
		s1 = NULL;
	}
	return (r);
}


char *lexer_charjoin(char *s1, char c)
{
	char			*r;
	unsigned int	i;

	if ((!s1 || s1 == NULL) && !c)
		return (NULL);
	i = 0;
	r = (char *)malloc(sizeof(char) * (term_strlen(s1) + 1 + 1));
	if (!r)
		return (NULL);
	while (s1 != NULL && s1 && s1[i] != '\0' && s1[i] != '\n')
	{
		r[i] = s1[i];
		i++;
	}
	r[i++] = c;
	r[i] = '\0';
	if (s1 && s1 != NULL)
		free(s1);
	return (r);
}

int	en(char *s)
{
	int	i;

	i = 0;
	if (!s || s == NULL || !s[i] || s[i] == '\0')
		return (0);
	while (s && s[i] && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ter(char *s2, int i)
{
	char *r;
	int len;

	len = en(s2);
	//r = (char *)malloc(sizeof(char) * (len + 1));
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


char	**strjoin_lex_mas(int len, t_for_in_lexer *lex)
{
	char	**lin;
	int		i;

	i = 0;
	lex->len = len;
	lin = (char **)malloc((len + 1) * sizeof(char *));
	if (!lin)
		return (NULL);
	while (lex->mas_line && lex->mas_line != NULL && lex->mas_line[i] && lex->mas_line[i] != NULL && i < len)
	{
		lin[i] = ter(lex->mas_line[i], -1);
		if (lex->mas_line[i])
		{
			free((void *)lex->mas_line[i]);
			lex->mas_line[i] = NULL;
		}
		i++;
	}
	lin[i++] = ter(lex->line, -1);
	lin[i] = NULL;
	if (lex->mas_line)
	{
		free((void **)lex->mas_line);
		lex->mas_line = NULL;
	}
	return (lin);
}

char	**strjoin_pr_mas(int len, char **s, char *line)
{
	char	**lin;
	int		i;

	i = 0;
	//par = (t_for_in_parser *)ft_calloc(2, sizeof(par));
	lin = (char **)ft_calloc(len + 1, sizeof(char *));
	//lin = (char **)malloc((len + 1) * sizeof(char *));
	if (!lin)
		return (NULL);
	while (i < len - 1 && s && s != NULL && s[i] && s[i] != NULL)
	{
		lin[i] = ter(s[i], -1);
		//printf("\nlin += |%s|\n", lin[i]);
		if (s[i])
		{
			free(s[i]);
			s[i] = NULL;
		}
		i++;
		if (!s[i])
			break ;
	}
	//printf("\n3'/++'\n");
	lin[i++] = ter(line, -1);
	lin[i] = NULL;
	if (s)
	{
		free((void **)s);
		s = NULL;
	}
	//printf("\n3''''''\n");
	return (lin);
}

