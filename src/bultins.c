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

int ft_do_exit(char **args)
{
	(void)args;
	return (0);
}

int ft_do_set(char **args)
{
	(void)args;
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
	(void)args;
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
	if (!ft_strcmp(args[i], "-n"))
	{
		newl = false;
		i++;
	}
	else
		newl = true;
	while (args[i])
		ft_putstr_fd(args[i++], 1);
	if (newl)
		ft_putstr_fd("\n", 1);
	return (0);
}

//No fork for builtin - because it leaks

int	ft_do_builtin(char *cmd, char **args)
{
	int sw;

	sw = ft_strstrchr((const char *)cmd, (const char **)BLT_IN);
	if (sw == 0)
		return (ft_do_echo(args));
	else if (sw == 1)
		return (ft_do_exit(args));
	if (sw == 2)
		return (ft_do_set(args));
	if (sw == 3)
		return (ft_do_unset(args));
	if (sw == 4)
		return (ft_do_export(args));
	if (sw == 5)
		return (ft_do_pwd(args));
	if (sw == 6)
		return (ft_do_cd(args));
	return (0);
}
