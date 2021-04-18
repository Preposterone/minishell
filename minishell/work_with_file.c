
#include "minishell.h"

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