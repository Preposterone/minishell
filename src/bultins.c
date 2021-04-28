/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:39:34 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/28 16:45:27 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_arr(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
		ft_putendl_fd(arr[i], 1);
}

/*
	Exit the shell, returning a status of n to the shell’s parent.
	If n is omitted, the exit status is that of the last command executed
*/
int ft_do_exit(char **args, t_for_in_terminal *t)
{
	long long int	reason;
	int				i;

	i = 0;
	ft_putendl_fd(EXIT, 1);
	while (args[i])
		i++;
	if (i > 1)
		; //TODO: print error, don't actually exit
	/* else if (i == 1)
	{
		reason =
	} */

	(void)args; //TODO: long long as exit status
	file_mas(t->mas_his, t->peri);
	exit (0);
}

int ft_do_env(char **args, char **envp_cpy)
{
	if (args[0])
		; //invalid argument error or should there be this
	else
		ft_print_arr(envp_cpy);
	return (0);
}

/**
 * Checks if each char in s is alpha but no more than slen chars
 */
static	bool ft_isstralpha(char *s, int slen)
{
	int		i;

	i = -1;
	while (++i < slen)
	{
		if (!ft_isalpha(s[i]))
			return (false);
	}
	return (true);
}
/*
	Remove each variable or function name. (from env)
	The return status is zero unless a name is readonly.
	or if identifier is invalid (only letters in key)
*/
int ft_do_unset(char **args, t_envp *sh_envp)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (ft_isstralpha(args[i], ft_strlen(args[i])))
		{
			ft_delete_envp_elem(args[i], sh_envp);
		}
	}

	return (0);
}
/*
	Mark each name to be passed to child processes in the environment.
	The return status is zero unless an invalid option is supplied, one of the names is not a valid shell variable name. (only letters in key)
*/
int ft_do_export(char **args, t_envp *sh_envp)
{
	int		i;
	int		equalslocation;
	char	*key;

	i = -1;
	while (args[++i])
	{
		equalslocation = ft_strchr_index(args[i], '=') + 1;
		// add check for alphabetic characters as key
		if (equalslocation != -1)
		{
			key = ft_strndup(args[i], equalslocation);
			ft_update_envp_elem(key, &args[i][equalslocation], sh_envp);
			free(key);
		}
	}
	return (0);
}
/*
	Print the absolute pathname of the current working directory.
	The return status is zero unless an error is encountered while determining the name of the current directory or an invalid option is supplied.
*/
int ft_do_pwd(char **args)
{
	char *buf;

	if (args[0])
		; //invalid argument error or should there be this
	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf)
	{
		ft_putendl_fd(buf, 1);
		free(buf);
	}
	return (0);
}
/*
	Change the current working directory to directory. If directory is not supplied, the value of the HOME shell variable is used. Any additional 	arguments following directory are ignored.
	The return status is zero if the directory is successfully changed, non-zero otherwise.
 */
int ft_do_cd(char **args, t_envp *env)
{
	char	*buf;
	char	*dir;

	buf = NULL;

	dir = args[0];
	if (!dir)
		dir = ft_get_envp_elem("HOME=", env);
	if (chdir(dir))
		perror(strerror(errno));	//do i print it this way?
	else
	{
		buf = getcwd(buf, 0);
		ft_update_envp_elem("PWD=", buf, env);
		free(buf);
	}
	return (0);
}
/*
	Output the args, separated by spaces, terminated with a newline.
	The return status is 0 unless a write error occurs
*/
int	ft_do_echo(char **args)
{
	int		i;
	bool	newl;

	i = 0;
	if (args[i] && !ft_strcmp(args[i], "-n"))
	{
		newl = false;
		i++;
	}
	else
		newl = true;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newl)
		ft_putstr_fd("\n", 1);
	return (0);
}

//No fork for builtin - because it leaks

int	ft_do_builtin(char *cmd, char **args, t_envp *envp,
			t_for_in_terminal *term_props)
{
	int sw;

	sw = ft_strstrchr((const char *)cmd, (const char **)BLT_IN);
	if (sw == 0)
		return (ft_do_echo(args));
	else if (sw == 1)
		return (ft_do_cd(args, envp));
	if (sw == 2)
		return (ft_do_pwd(args));
	if (sw == 3)
		return (ft_do_export(args, envp));
	if (sw == 4)
		return (ft_do_unset(args, envp));
	if (sw == 5)
		return (ft_do_env(args, envp->sh_envp));
	if (sw == 6)
		return (ft_do_exit(args, term_props));
	return (0);
}
