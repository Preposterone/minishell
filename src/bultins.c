/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:39:34 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/12 11:10:44 by aarcelia         ###   ########.fr       */
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

int ft_do_env(char **envp_cpy)
{
	ft_print_arr(envp_cpy);
	return (0);
}

/**
 * Checks if each char in s is alpha but no more than slen chars
 */
bool ft_isstralpha(char *s, int slen)
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
	int	ret;

	i = -1;
	ret = 0;
	while (args[++i])
	{
		if (is_id_str_valid(args[i]))
			ft_delete_envp_elem(args[i], sh_envp);
		else
		{
			ft_puterr_arr((char *[]) {"unset: '", args[i], MSH_ID_INV, NULL});
			ret = 1;
		}
	}
	return (ret);
}

/*
	Print the absolute pathname of the current working directory.
	The return status is zero unless an error is encountered while
	determining the name of the current directory or an invalid option is supplied.
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

	sw = ft_strstrchr((const char *)cmd, (const char *[]){"echo",\
				"cd","pwd","export","unset","env","exit",NULL});
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
		return (ft_do_env(envp->sh_envp));
	if (sw == 6)
		return (ft_do_exit(args, term_props, !envp->ispipe));
	return (0);
}
