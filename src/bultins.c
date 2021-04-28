/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:39:34 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/23 18:39:12 by aarcelia         ###   ########.fr       */
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

int ft_do_exit(char **args, t_for_in_terminal *t)
{
	(void)args;
	ft_putendl_fd(EXIT, 1);
	file_mas(t->mas_his, t->peri);
	// write(1, EXIT, term_strlen(EXIT)); //todo
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

int ft_do_unset(char **args)
{
	(void)args;
	return (0);
}

int ft_do_export(char **args)
{
	(void)args;
	return (0);
}

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

int ft_do_cd(char **args)
{
	(void)args;
	return (0);
}

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
		return (ft_do_cd(args));
	if (sw == 2)
		return (ft_do_pwd(args));
	if (sw == 3)
		return (ft_do_export(args));
	if (sw == 4)
		return (ft_do_unset(args));
	if (sw == 5)
		return (ft_do_env(args, envp->sh_envp));
	if (sw == 6)
		return (ft_do_exit(args, term_props));
	return (0);
}
