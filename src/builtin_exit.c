/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:52:12 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/13 19:00:45 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	iswrd_di(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ')
	{
		if (!ft_isdigit(s[i++]))
			return (false);
	}
	return (true);
}

static int	ft_exit_err(char *str)
{
	if (!str)
	{
		ft_puterr_arr((char *[]){"exit: ", MSH_EXT_ARGS, NULL});
		return (1);
	}
	else
	{
		ft_puterr_arr((char *[]){"exit: ", str, ": ", MSH_EXT_NUMER, NULL});
		return (255);
	}
}

static bool	ft_validate_ex_arg(char *arg)
{
	if ((arg[0] == '-' && ft_strlen(&arg[1]) > 19)
		|| (arg[0] != '-' && ft_strlen(arg) > 19)
		|| (arg[0] != '-' && !iswrd_di(arg))
		|| (arg[0] != '-' && !iswrd_di(&arg[1])))
		return (true);
	return (false);
}

static void	ft_exit_final(u_char exit_code, int64_t reason, bool do_exit,
				t_for_in_terminal *t)
{
	if (exit_code == 0)
		exit_code = (u_char)reason;
	g_all.exit_code = exit_code;
	if (do_exit)
	{
		file_mas(t->mas_his, t->peri, t);
		exit(exit_code);
	}
}

/*
	Exit the shell, returning a status of n to the shell’s parent.
	If n is omitted, the exit status is that of the last command executed
	exit status = args[0] % 256
*/
/**
 * Check if args[0] is all number (with or without '-'),
 * if not - give error, don't exit
 * else check if there are more than 2 args
 */
int	ft_do_exit(char **args, t_for_in_terminal *t, bool print)
{
	bool	do_exit;
	int64_t	reason;
	u_char	exit_code;
	char	*arg;

	if (print)
		ft_putendl_fd(EXITT, 2);
	do_exit = true;
	reason = 0LL;
	exit_code = 0;
	arg = ft_strtrim(args[0], " ");
	if (!args[0])
		reason = 0LL;
	else if (ft_validate_ex_arg(arg))
		exit_code = ft_exit_err(args[0]);
	else if (args[1])
	{
		exit_code = ft_exit_err(NULL);
		do_exit = false;
	}
	else
		reason = ft_atoll(arg);
	free(arg);
	ft_exit_final(exit_code, reason, do_exit, t);
	return (exit_code);
}
