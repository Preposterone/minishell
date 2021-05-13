/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:52:09 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/13 18:38:53 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_print_arr_prepend(char **arr, char *prepend)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		ft_putstr_fd(prepend, 1);
		ft_putendl_fd(arr[i], 1);
	}
	return (0);
}

/**
 * @param args is a key=value pair
 * where @key has syntax:	xx123=
 * 							xxxxx=
 * 							_123x=
 * 							_x123=
 */
bool	is_id_str_valid(char *id)
{
	int		i;

	i = -1;
	if (!ft_isalpha(id[0]) && id[0] != '_')
		return (false);
	while (id[++i] && id[i] != '=')
	{
		if (!ft_isalnum(id[i]) && id[i] != '_' && id[i] != '=')
			return (false);
	}
	return (true);
}

/*
	Mark each name to be passed to child processes in the environment.
	The return status is zero unless an invalid option is supplied,
	one of the names is not a valid shell variable name.
*/
int	ft_do_export(char **args, t_envp *sh_envp)
{
	int		i;
	int		equalslocation;
	char	*key;
	int		ret;

	i = -1;
	ret = 0;
	if (!args[0])
		return (ft_print_arr_prepend(sh_envp->sh_envp, "declare -x "));
	while (args[++i])
	{
		equalslocation = ft_strchr_index(args[i], '=');
		key = ft_strndup(args[i], equalslocation + 1);
		if (!key)
			exit_fatal(MSH_MALLOC_EXIT);
		else if (is_id_str_valid(key) && equalslocation != -1)
			ft_update_envp_elem(key, &args[i][equalslocation + 1], sh_envp);
		else
		{
			ft_puterr_arr((char *[]){"export: '", args[i], MSH_ID_INV, NULL});
			ret = 1;
		}
		free(key);
	}
	return (ret);
}
