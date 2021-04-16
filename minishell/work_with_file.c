
#include <fcntl.h>
#include <fcntl.h>


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