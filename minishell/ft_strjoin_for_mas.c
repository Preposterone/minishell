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

char	**strjoin_for_mas(int len, char **s, char *line)
{
	char	**lin;
	int		i;

	i = 0;
	lin = (char **)malloc((len + 1) * sizeof(char *));
	if (!lin)
		return (NULL);
	while (s && s[i] != NULL && i < len)
	{
		lin[i] = (char *)malloc((ft_strlen(s[i]) + 1) * sizeof(char));
		if (!lin[i])
			return (NULL);
		lin[i] = ft_strjoin(NULL, s[i]);
		if (s[i])
			free((void *)s[i]);
		i++;
	}
	lin[i] = (char *)malloc((ft_strlen(line) + 1) * sizeof(char));
	if (!lin[i])
		return (NULL);
	lin[i] = ft_strjoin(NULL, line);
	lin[++i] = NULL;
	if (s)
		free((void **)s);
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
		free((void *)h_const);
	return (r);
}
