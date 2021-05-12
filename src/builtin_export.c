/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:52:09 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/12 16:41:33 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void swap(const char **a, const char **b)
{
	const char *temp = *a;
	*a = *b;
	*b = temp;
}

void		ft_quicksort_recursive(char **str, int first, int last)
{
	int			pivot;
	int			i;
	int			j;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;
		while (i < j)
		{
			while (str[i].dist >= str[pivot].dist && i < last)
				i++;
			while (str[j].dist < str[pivot].dist)
				j--;
			if (i < j)
				ft_swaps(str, i, j);
		}
		ft_swaps(str, pivot, j);
		ft_quicksort_recursive(str, first, j - 1);
		ft_quicksort_recursive(str, j + 1, last);
	}
}*/

static int	ft_print_arr_prepend(char **arr, char *prepend)
{
	int i;

	i = -1;
	while (arr[++i])
	{
		ft_putstr_fd(prepend,1);
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
//TODO: fix return code
int ft_do_export(char **args, t_envp *sh_envp)
{
	int		i;
	int		equalslocation;
	char	*key;
	int		ret;

	i = -1;
	if (!args[0])
		return (ft_print_arr_prepend(sh_envp->sh_envp, "declare -x "));
	while (args[++i])
	{
		equalslocation = ft_strchr_index(args[i], '=');
		key = ft_strndup(args[i], equalslocation + 1);
		if (!key)
			exit_fatal(MSH_MALLOC_EXIT);
		else if (is_id_str_valid(key) && equalslocation != -1)
		{
			ft_update_envp_elem(key, &args[i][equalslocation + 1], sh_envp);
			ret = 0;
		}
		else
		{
			ft_puterr_arr((char *[]) {"export: '", args[i], MSH_ID_INV, NULL});
			ret = 1;
		}
		free(key);
	}
	return (ret);
}
