/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:52:09 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/14 13:52:17 by aarcelia         ###   ########.fr       */
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

static char	*ft_insert_quotes(char *s)
{
	char	*ret;
	char	*value;
	char	*tmp;
	int		equals;

	equals = ft_strchr_index(s, '=');
	value = ft_strdup(&s[equals + 1]);
	tmp = ft_strjoin("\"", value);
	free(value);
	value = ft_strjoin(tmp, "\"");
	free(tmp);
	tmp = ft_strndup(s, equals + 1);
	ret = ft_strjoin(tmp, value);
	free(tmp);
	free(value);
	return (ret);
}

static char	**ft_add_quotes(char **envp)
{
	char	**ret;
	int		count;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	count = i;
	ret = ft_calloc(count + 1, sizeof(char *));
	i = -1;
	while (++i < count)
		ret[i] = ft_insert_quotes(envp[i]);
	ft_quicksort_char_arr(ret, (uint)i);
	return (ret);
}

/*split by key*/
static int	ft_run_export_print(t_envp *sh_envp)
{
	char	**buf;

	buf = ft_add_quotes(sh_envp->sh_envp);
	ft_print_arr_prepend(buf, "declare -x ");
	ft_free_arr(buf);
	return (1);
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
		return (ft_run_export_print(sh_envp));
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
