#include "termcap.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s || s == NULL || !s[i])
		return (0);
	while (s[i] && s[i] != '\0')
		i++;
	return (i);
}

int	ft_strlen_mas(char **s)
{
	int	i;

	i = 0;
	if (!s || !s[i] || s[0] == NULL)
		return (0);
	while (s[i] && s[i] != NULL)
		i++;
	return (i);
}

char	**strjoin_for_mas(int len, t_for_in_terminal *t, char *line)
{
	char	**lin;
	int		i;

	i = 0;
	lin = (char **)malloc((len + 1) * sizeof(char *));
	if (!lin)
		return (NULL);
	while (t->mas_his && t->mas_his[i] != NULL && i < len)
	{
		lin[i] = ft_strjoin(NULL, t->mas_his[i]);
		if (t->mas_his[i])
		{
			free((void *)t->mas_his[i]);
			t->mas_his[i] = NULL;
		}
		i++;
	}
	lin[i] = ft_strjoin(NULL, line);
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

char	*get_h_const(char *h_const)
{
	char	*r;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!h_const)
		return (NULL);
	while (h_const[i] && h_const[i] != '\n')
		i++;
	r = malloc(sizeof(char) * ((my_strlen(h_const) - i) + 1));
	if (!r)
		return (NULL);
	i++;
	while (h_const[i])
		r[j++] = h_const[i++];
	r[j] = '\0';
	if (h_const)
	{
		free((void *)h_const);
		h_const = NULL;
	}
	return (r);
}
