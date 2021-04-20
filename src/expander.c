/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:58:17 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/20 18:59:52 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Copy of incoming enviroment variables
 * should be ran once at execution start
 */

static void	ft_envp_cpy(char *envp[], t_envp *buf)
{
	int		i;
	char	**envp_cpy;
	char	*path;

	i = -1;
	while (envp[++i])
		;
	envp_cpy = (char **)ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (envp[++i])
	{
		envp_cpy[i] = ft_strdup(envp[i]);
		if (!ft_strncmp(envp[i], "PATH=", 5))
			path = &envp_cpy[i][5];
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
			break;
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
	split_path = ft_split(path, ':');
	while (split_path[++i])
	{
		dir = opendir(split_path[i]);
		if (dir)
		{
			if (ft_isfileindir(cmd, dir, len))
				break;
		}
	}
	return (ft_freesplit_and_ret(split_path, i));
}

int	main(int argc, char *argv[], char *envp[])
{
	t_envp	sh_envp;
	(void)argv;
	(void)argc;
	char	*cmdpath;
	char	cmd[100];

	ft_bzero(&sh_envp, sizeof(sh_envp));
	ft_envp_cpy(envp, &sh_envp);
	for (int i = 0; i < 10; i++)
	{
		ft_bzero(&cmd, 100);
		scanf("%s", cmd);
		cmdpath = expander(cmd, sh_envp.sh_path);
		if (!cmdpath)
		{
			ft_putendl_fd(MINISHELL ": la" ERR_CMD_NOT_FOUND, 2);
		}
		else
			printf("%s\n", cmdpath);
		free(cmdpath);
	}
	return (0);
}
