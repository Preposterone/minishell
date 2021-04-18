
#include "minishell.h"





void				*my_memmove(void *dst,
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







size_t	my_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char				*my_strjoin(char const *s1, char const *s2)
{
	size_t			s1_len;
	size_t			s2_len;
	size_t			all_len;
	char			*r;

	if (!s1 && !s2)
		return (0);
	s1_len = my_strlen((char *)s1);
	s2_len = my_strlen((char *)s2);
	all_len = s1_len + s2_len + 1;
	if (!(r = malloc(sizeof(char) * all_len)))
		return (NULL);
	if (!r)
		return (0);
	my_memmove(r, s1, s1_len);
	my_memmove(r + s1_len, s2, s2_len);
	r[all_len - 1] = '\0';
	free((char *)s1);
	return (r);
}


int		my_return(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
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
	if (!h_const[i])
	{
		free(h_const);
		return (NULL);
	}
	if (!(r = malloc(sizeof(char) * ((my_strlen(h_const) - i) + 1))))
		return (NULL);
	i++;
	while (h_const[i])
		r[j++] = h_const[i++];
	r[j] = '\0';
	free(h_const);
	return (r);
}

char	*get_line(char *str)
{
	int		i;
	char	*r;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!(r = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		r[i] = str[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

int		get_next_line(int fd, char **line)
{
	char			*buff;
	static char		*h_const;
	int				reader;

	reader = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0 || (read(fd, 0, 0) == -1))
		return (0);
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (0);
	while (!my_return(h_const) && reader != 0)
	{
		if ((reader = read(fd, buff, BUFFER_SIZE)) == -1)
		{
			free(buff);
			return (-1);
		}
		buff[reader] = '\0';
		h_const = my_strjoin(h_const, buff);
	}
	free(buff);
	*line = get_line(h_const);
	h_const = get_h_const(h_const);
	if (reader == 0)
		return (0);
	return (1);
}
