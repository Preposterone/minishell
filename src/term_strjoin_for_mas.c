#include "termcap.h"

int	term_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s || s == NULL || !s[i])
		return (0);
	while (s[i] && s[i] != '\0')
		i++;
	return (i);
}

int	term_strlen_mas(char **s)
{
	int	i;

	i = 0;
	if (!s || !s[i] || s[0] == NULL)
	{
		return (0);
	}
	if (!s[i])
		return (0);
	while (s[i] && s[i] != NULL)
	{
		i++;
		if (!s[i])
			break ;
	}
	return (i);
}

char	**strjoin_for_mas(int len, t_for_in_terminal *t, char *line)
{
	char	**lin;
	int		i;

	i = 0;
	lin = (char **)ft_calloc((len + 1), sizeof(char *));
	if (!lin)
		return (NULL);
	while (t->mas_his && t->mas_his[i] != NULL && i < len) //just len - 1
	{
		lin[i] = term_strjoin(NULL, t->mas_his[i]);
		if (t->mas_his[i])
		{
			free(t->mas_his[i]);
			t->mas_his[i] = NULL;
		}
		i++;
	}
	lin[i] = term_strjoin(NULL, line);
	lin[++i] = NULL;
	if (t->mas_his)
	{
		free((void **)t->mas_his);
		t->mas_his = NULL;
	}
	return (lin);
}

void	*my_memmove(void *dst,
		const void *src, size_t len)
{
	unsigned char	*j;
	unsigned char	*b;

	j = (unsigned char *)src;
	b = (unsigned char *)dst;
	if (!b && !j)
		return (b);
	if (b < j)
	{
		while (len--)
			*b++ = *j++;
	}
	else
	{
		b += len;
		j += len;
		while (len--)
			*--b = *--j;
	}
	return (dst);
}

int	gnl_second(int reader, char **buff)
{
	if (*buff)
	{
		free((void *)*buff);
		*buff = NULL;
	}
	if (reader == 0)
		return (0);
	return (1);
}
