/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:58:17 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/23 17:30:14 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isbuiltin(char *cmd)
{
	int		i;
	bool	ret;

	i = -1;
	ret = false;
	if (cmd)
	{
		while (BLT_IN[++i])
		{
			if (!ft_strcmp(cmd, BLT_IN[i]))
			{
				ret = true;
				break;
			}
		}
	}
	return (ret);
}

/**
 * Copy of incoming enviroment variables
 * should be ran once at execution start
 */

void	ft_envp_cpy(const char *envp[], t_envp *buf)
{
	int		i;
	char	**envp_cpy;
	char	*path;

	i = 0;
	while (envp[i])
		i++;
	envp_cpy = (char **)ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (envp[++i])
	{
		envp_cpy[i] = ft_strdup(envp[i]);
		if (!ft_strncmp(envp[i], "PATH=", 5))
			path = &envp_cpy[i][5];
		else if (!ft_strncmp(envp[i], "TERM=", 5))
			buf->sh_term = &envp_cpy[i][5];
	}
	buf->sh_envp = envp_cpy;
	buf->sh_path = path;
}

static char	*ft_freesplit_and_ret(char **s, int upto)
{
	char	*ret;
	int		i;

	i = -1;
	ret = s[upto];
	while (s[++i])
	{
		if (i != upto)
		{
			free(s[i]);
			s[i] = NULL;
		}
	}
	free(s);
	s = NULL;
	return (ret);
}

static bool	ft_isfileindir(char *filename, DIR *dir, int len)
{
	struct dirent	*entry;
	bool			ret;

	entry = readdir(dir);
	ret = false;
	while (entry)
	{
		if (entry->d_namlen == len && !ft_strcmp(entry->d_name, filename))
		{
			ret = true;
			break ;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (ret);
}

char	*expander(char *cmd, char *path)
{
	DIR				*dir;
	int				i;
	int				len;
	char			**split_path;

	len = (int)ft_strlen(cmd);
	i = -1;
	if (ft_isbuiltin(cmd))
	{
		printf("Running builtin\n");//todo: return cmd to executor
		return cmd;
	}
	else if (!path)
	{
		printf("Path is NULL\n");//todo: print error and goto termcap
		return NULL;
	}
	split_path = ft_split(path, ':');
	while (split_path[++i])
	{
		dir = opendir(split_path[i]);
		if (dir)
		{
			if (ft_isfileindir(cmd, dir, len))
				break ;
		}
	}
	return (ft_freesplit_and_ret(split_path, i));
}
