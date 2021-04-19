    /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_gnl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:35:42 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/18 13:10:13 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

/*
** A function which frees all memory allocated to static var 'rem' and points
** 'rem' at NULL;
*/

static int			ft_free_ret(char **rem)
{
	if (*rem)
	{
		free(*rem);
		*rem = NULL;
	}
	return (-1);
}

/*
** A function which reads static var 'rem'.
** If null terminator found in 'rem':
** frees *rem, points it at NULL
** RETURN VALUES:
** 0: didn't find '\0'
** -1: failed malloc
*/

static int			ft_verify_eof(char **rem, char **line)
{
	if (ft_strchr(*rem, '\0'))
	{
		if (!(*line = ft_strdup(*rem)))
			return (-1);
		free(*rem);
		*rem = NULL;
	}
	return (0);
}

/*
** A function which reads static var 'rem'.
** If newline found in 'rem':
** in place of newline, writes null terminator, writes everything up to '\0'
** into 'line', points 'rem' at next character if it exists.
** if no new line found, ft_verify_eof called
** RETURN VALUES:
** 1: found new line
** 0: didn't find '\0'
** -1: failed malloc
*/

static int			ft_validate_rem(char **rem, char **line)
{
	char	*s1;
	char	*s2;

	if ((s1 = ft_strchr(*rem, '\n')))
	{
		*s1 = '\0';
		if (!(*line = ft_strdup(*rem)))
			return (-1);
		if (!(s2 = ft_strdup(s1 + 1)))
			return (-1);
		free(*rem);
		*rem = s2;
		return (1);
	}
	return (ft_verify_eof(&*rem, &*line));
}

/*
** A function which returns a line read from a file descriptor,
** without the newline
** Return values:
** 1:  A line has been read
** 0 :  EOF has been reached
** -1 :  An error happened
** Parameters:
** int fd.  file descriptor for reading
** char **line.  The value of what has been read
*/

int					get_next_line(int fd, char **line)
{
	static char *rem;
	char		*buffer;
	char		*tmp;
	int			readbytes;

	buffer = NULL;
	if ((fd < 0 || fd > 1024) != 0 || read(fd, buffer, 0) < 0
		|| !line || !(buffer = (char*)malloc(BUFFER_SIZE + 1)))
		return (-1);
	if (!rem)
		rem = ft_strdup("");
	while ((readbytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[readbytes] = '\0';
		tmp = ft_strjoin(rem, buffer);
		free(rem);
		rem = tmp;
		if (ft_strchr(rem, '\n'))
			break ;
	}
	free(buffer);
	return (readbytes < 0 ? ft_free_ret(&rem)
	: ft_validate_rem(&rem, &*line));
}
