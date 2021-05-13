#include "minishell.h"

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
