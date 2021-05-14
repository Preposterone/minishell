/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:52:15 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/14 16:36:40 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//cd: error retrieving current directory:
// getcwd: cannot access parent directories: No such file or directory

static int	ft_do_chdir(char *dir, t_envp *env)
{
	char	*buf;
	int		ret;

	buf = NULL;
	if (chdir(dir) == -1)
	{
		ft_puterr_arr((char *[]){"cd: ", dir, ": ", strerror(errno), NULL});
		ret = 1;
	}
	else
	{
		buf = getcwd(buf, 0);
		if (!buf)
		{
			ft_puterr_arr((char *[]){"cd: ", MSG_CD_1, MSG_CD_2, NULL});
		}
		else
		{
			ft_update_envp_elem("PWD=", buf, env);
			free(buf);
		}
		ret = 0;
	}
	return (ret);
}

static int	ft_do_cd_home(t_envp *env)
{
	char	*home;
	int		ret;

	home = ft_get_envp_elem("HOME=", env);
	if (!home)
	{
		ft_puterrln("cd: HOME not set");
		ret = 1;
	}
	else
		ret = ft_do_chdir(home, env);
	return (ret);
}

/*
	Change the current working directory to directory.
	If directory is not supplied, the value of the HOME shell variable is used.
	Any additional 	arguments following directory are ignored.
	The return status is zero if the directory is successfully changed,
	non-zero otherwise.
 */

int	ft_do_cd(char **args, t_envp *env)
{
	char	*dir;

	dir = args[0];
	if (!dir)
		return (ft_do_cd_home(env));
	else
		return (ft_do_chdir(dir, env));
}
