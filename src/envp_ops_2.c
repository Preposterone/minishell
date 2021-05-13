/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_ops_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:44:17 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/13 18:44:45 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Searches for key in sh_envp struct, if found -> set to value, else,
 * create new element of sh_envp
 * Key: "xxx=" or "_xxx="
 */

void	ft_update_envp_elem(char *key, char *value, t_envp *sh_envp)
{
	int		index;
	int		cmplen;
	char	*newelem;

	cmplen = ft_strlen(key);
	index = ft_strstrchr1(key, (const char **)sh_envp->sh_envp, cmplen);
	newelem = ft_strjoin(key, value);
	if (index == -1)
	{
		ft_add_to_envp(sh_envp->sh_envp, newelem, sh_envp);
		free(newelem);
	}
	else
	{
		free(sh_envp->sh_envp[index]);
		sh_envp->sh_envp[index] = newelem;
	}
}

char	*ft_get_envp_elem(char *key, t_envp *sh_envp)
{
	int	index;
	int	cmplen;

	cmplen = ft_strlen(key);
	index = ft_strstrchr1(key, (const char **)sh_envp->sh_envp, cmplen);
	if (index != -1)
	{
		return (&sh_envp->sh_envp[index][cmplen]);
	}
	return (NULL);
}
