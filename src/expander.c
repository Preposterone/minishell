/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:58:17 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/13 17:46:11 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (LENCHECK !ft_strcmpl(entry->d_name, filename))
		{
			ret = true;
			break ;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (ret);
}

/* If found file locally, check if it's a directory or can be executed */
static char	*ft_validate_ret(char *file, char *dir)
{
	char		*abs_file;
	struct stat	buf;

	abs_file = ft_strstrjoin(file, dir);
	stat(abs_file, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
		exit_minishell(file, MSH_IS_DIR_ERR, NULL);
	else if (!(buf.st_mode & X_OK))
	{
		ft_puterr_arr((char *[]){file, MSH_PERM_DENIED, NULL});
		exit(126);
	}
	return (dir);
}

/*search locally for file named cmd if not found, return NULL*/
static char *ft_perform_local_search(char *cmd)
{
	DIR		*dir;
	char	*buf;
	char	*ret;

	buf = getcwd(NULL, 0);
	dir = opendir(buf);
	if (!dir)
		exit_fatal(MSH_MALLOC_EXIT);
	if (ft_isfileindir(cmd, dir, ft_strlen(cmd)))
		ret = ft_validate_ret(cmd, buf);
	else
		ret = NULL;
	return (ret);
}

// fprintf(stderr, "[EXPANDER]: Path not null search in path for '%s' in '%s'\n"\
// , cmd, split_path[i]);
// fprintf(stderr, "[EXPANDER]: File '%s' found!\n", cmd);

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
		// printf("Running builtin\n");	//TODO: return cmd to executor
		return cmd;
	}
	if (!path)
	{
		printf("Path is NULL\n");	//TODO: print error and goto termcap
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
