#include "minishell.h"

int	term_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	if (!s1 || !s2)
		return (1);
	c1 = (unsigned char)s1[i];
	c2 = (unsigned char)s2[i];
	while (c1 == c2)
	{
		if (!c1)
			return (c1 - c2);
		i++;
		c1 = (unsigned char)s1[i];
		c2 = (unsigned char)s2[i];
	}
	return (c1 - c2);
}

int	file(char *str)
{
	int	fd;

	if (!str)
		return (0);
	fd = open(FILE_HISTORY, O_CREAT | O_APPEND | O_RDWR, 00644);
	if (fd == -1)
		return (-1);
	write(fd, str, term_strlen(str));
	close(fd);
	return (0);
}

void	from_file(t_for_in_terminal *t)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(FILE_HISTORY, O_CREAT | O_APPEND | O_RDWR, 00644);
	if (fd == -1)
		return ;
	while (term_get_next_line(fd, &line, 1))
	{
		t->mas_his = strjoin_for_mas(term_strlen_mas(t->mas_his)
				+ 1, t, line);
		i++;
		if (line)
		{
			free((void *)line);
			line = NULL;
		}
	}
	if (line)
	{
		free((void *)line);
		line = NULL;
	}
	close(fd);
}


int	file_mas(char **str, int i, t_for_in_terminal *t)
{
	int fd;

	if (!str)
		return (0);
	fd = open(FILE_HISTORY, O_CREAT | O_APPEND | O_RDWR, 00644);
	if (fd == -1)
		return (-1);
	while (str[i] != NULL)
	{
		if (term_strcmp("\n", str[i]) && str[i][0] != 0 && str[i][0] != 4
			&& str[i][0] != 10)
		{
			write(fd, str[i], term_strlen(str[i]));
			write(fd, "\n", 1);
		}
		i++;
	}
	close(fd);
	del_settings_term(t);
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
	r = (char *)ft_calloc((my_strlen(h_const) - i) + 1, sizeof(char));
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

int	open_APPEND_file_redirect(char *s)
{
	int fd;

	if (!s)
		return (0);
	fd = open(s, O_CREAT | O_APPEND | O_RDWR, 00644);
	if (fd <= 0)
	{
		ft_puterr_arr((char *[]){s, ": ", strerror(errno), NULL});
		return (-1);
	}
	return (fd);
}

int	open_RDONLY_file_redirect(char *s)
{
	int fd;

	if (!s)
		return (0);
	fd = open(s, O_RDONLY, 00644);
	if (fd <= 0)
	{
		ft_puterr_arr((char *[]){s, ": ", strerror(errno), NULL});
		return (-1);
	}
	return (fd);
}

int	open_TRUNC_file_redirect(char *s)
{
	int fd;

	if (!s)
		return (0);
	fd = open(s, O_CREAT | O_TRUNC | O_RDWR, 00644);
	if (fd <= 0)
	{
		ft_puterr_arr((char *[]){s, ": ", strerror(errno), NULL});
		return (-1);
	}
	return (fd);
}

int check_file(char *s, int x, int y)
{
	x = open(s, O_WRONLY);
	if (x > 0)
	{
		close(x);
		x = 1;
	}
	else
		x = 0;
	y = open(s, O_RDONLY);
	if (y > 0)
	{
		close(y);
		y = 1;
	}
	else
		y = 0;
	if (x == 1 && y == 1)
		return 1;//фаил
	else if (x == 0 && y == 0)
		return 2;//не сущ
	else if (x == 0 && y == 1)
		return 3;//dir
	return 0;
}
