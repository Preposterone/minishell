#include "termcap.h"

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

char	*my_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	all_len;
	char	*r;

	if (!s1 && !s2)
		return (0);
	s1_len = my_strlen((char *)s1);
	s2_len = my_strlen((char *)s2);
	all_len = s1_len + s2_len + 1;
	r = (char *)malloc(sizeof(char) * all_len);
	if (!r)
		return (NULL);
	my_memmove(r, s1, s1_len);
	my_memmove(r + s1_len, s2, s2_len);
	r[all_len - 1] = '\0';
	if (s1)
	{
		free((char *)s1);
		s1 = NULL;
	}
	return (r);
}

int	my_return(char *str)
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

char	*get_line(char *str)
{
	int		i;
	char	*r;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	r = (char *)malloc(sizeof(char) * (i + 1));
	if (!r)
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

int	term_get_next_line(int fd, char **line, int reader)
{
	char		*buff;
	static char	*h_const;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || (read(fd, 0, 0) == -1))
		return (0);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	while (!my_return(h_const) && reader != 0)
	{
		reader = read(fd, buff, BUFFER_SIZE);
		if (reader == -1)
		{
			free((void *)buff);
			buff = NULL;
			return (-1);
		}
		buff[reader] = '\0';
		h_const = my_strjoin(h_const, buff);
	}
	*line = get_line(h_const);
	h_const = get_h_const(h_const);
	return (gnl_second(reader, &buff));
}
