/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:42:33 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/14 18:32:03 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		ft_putendl_fd(arr[i], 1);
}

int	ft_do_env(char **envp_cpy)
{
	ft_print_arr(envp_cpy);
	return (0);
}

/**
 * If no pipe => dups last argument
 * else, dups "";
 */

void	ft_update_last_arg(t_for_in_parser **par, t_envp *sh_envp)
{
	int		i;
	char	*buf;

	buf = NULL;
	if (par[0]->key != 1)
		buf = NULL;
	else
	{
		i = -1;
		while (par[0]->arguments[++i])
			buf = par[0]->arguments[i];
	}
	if (!buf)
		buf = ft_strdup("");
	else
		buf = ft_strdup(buf);
	ft_update_envp_elem("_=", buf, sh_envp);
	free(buf);
}
