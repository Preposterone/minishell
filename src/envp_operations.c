/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 11:34:27 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/03 16:53:51 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}

/**
 * Makes a copy of char **envp, frees *envp, sh_path, sh_term
*/
void	ft_add_to_envp(char **envp, char *add, t_envp *sh_envp)
{
	char	**buf;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
		i++;
	buf = (char **)ft_calloc(i + 2, sizeof(char *));
	if (!buf)
		exit_fatal(MSH_MALLOC_EXIT);
	j = -1;
	while (++j < i)
		buf[j] = envp[j];
	buf[j] = ft_strdup(add);
	free(envp);
	ft_envp_cpy((const char **)buf, sh_envp);
	ft_free_arr(buf);
}

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

static char **ft_envp_pop_elem(char **envp, int skip)
{
	char	**buf;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (envp[i])
		i++;
	buf = (char **)ft_calloc(i, sizeof(char *));
	if (!buf)
		exit_fatal(MSH_MALLOC_EXIT);
	j = 0;
	k = 0;
	while (j < i)
	{
		if (j != skip)
		{
			buf[k] = ft_strdup(envp[j]);
			k++;
		}
		j++;
	}
	ft_free_arr(envp);
	return (buf);
}

int	ft_delete_envp_elem(char *key, t_envp *sh_envp)
{
	char	*buf;
	int		index;
	int		cmplen;
	char	**envp_popped;

	buf = ft_strjoin(key, "=");
	if (!buf)
		exit_fatal(MSH_MALLOC_EXIT);
	cmplen = ft_strlen(buf);
	index = ft_strstrchr1(buf, (const char **)sh_envp->sh_envp, cmplen);
	if (index != -1)
	{
		envp_popped = ft_envp_pop_elem(sh_envp->sh_envp, index);
		ft_envp_cpy((const char **)envp_popped, sh_envp);
		ft_free_arr(envp_popped);
	}
	free(buf);
	return (1);
}
