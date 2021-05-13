#include "minishell.h"


char	*term_strjoin_n(char *s2, char *r, int i)
{
	r = (char *)ft_calloc((term_strlen(s2) + 1), sizeof(char));
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
	r = (char *)ft_calloc((term_strlen(s1) + term_strlen(s2) + 1), sizeof(char));
	if (!r)
		return (NULL);
	while (s1[i])
	{
		if (s1[i] == '\n' && s1[i + 1] == '\0')
			break ;
		r[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2[++j])
	{
		if (s1[i] == '\n' && s1[i + 1] == '\0')
			break ;
		r[i++] = s2[j];
	}
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
	r = (char *)ft_calloc((strlen(s1)), sizeof(char));
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
	r = (char *)ft_calloc((term_strlen(s1) + 1 + 1), sizeof(char));
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


