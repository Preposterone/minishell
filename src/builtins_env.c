/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:42:33 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/13 18:42:36 by aarcelia         ###   ########.fr       */
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
