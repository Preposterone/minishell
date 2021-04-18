
#include "minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
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

int file(char *str)
{
    int fd;
    int fdf;
    int i;

    i = 0;
    if (!str)
        return (0);
    fd = open("minishell_history", O_CREAT | O_APPEND | O_RDWR, 00644);
	if (fd == -1)
		return (-1);
    write(fd, str, strlen(str));
    close(fd);
    return (0);
}

void from_file(t_for_in_terminal *t)
{
    int fd;
    int i;
    char *line;


    i = 0;
    fd = open("minishell_history", O_CREAT | O_APPEND | O_RDWR, 00644);
	if (fd == -1)
		return ;
    while (get_next_line(fd, &line))
    {
        t->mas_his = strjoin_for_mas(ft_strlen_mas(t->mas_his)+1, t->mas_his, line);
    }
    close(fd);
}

int file_mas(char **str, int i)
{
    int fd;

    if (!str)
        return (0);
    fd = open("minishell_history", O_CREAT | O_APPEND | O_RDWR, 00644);
	if (fd == -1)
		return (-1);
    while (str[i] != NULL)
    {
        if (ft_strcmp("\n", str[i]) && str[i][0] != 0 && str[i][0] != 4 && str[i][0] != 10)
        {
            write(fd, str[i], strlen(str[i]));
            write(fd, "\n", 1);
        }
        i++;
    }
    close(fd);
    return (0);
}

/*
char **his_from_file()
{
	int fd;
	char *line;
	char **line_all;

    fd = open("minishell_history", O_CREAT | O_APPEND | O_RDWR, 00644);
	if (fd == -1)
		return NULL;
	while (get_next_line(fd, &line) > 0)
		line_all = strjoin_for_mas(ft_strlen_mas(line_all), line_all, line);
	if (line != NULL)
		line_all = strjoin_for_mas(ft_strlen_mas(line_all), line_all, line);
    close(fd);
	return (line_all);
}
*/