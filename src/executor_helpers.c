/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:52:01 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/13 18:52:08 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isbuiltin(char *cmd)
{
	int		i;
	bool	ret;
	char	**s;

	i = -1;
	ret = false;
	s = (char *[]){"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	if (cmd)
	{
		while (s[++i])
		{
			if (!ft_strcmp(cmd, s[i]))
			{
				ret = true;
				break ;
			}
		}
	}
	return (ret);
}

void	ft_freematrix(void **target)
{
	int	i;

	i = -1;
	while (target[++i])
		free(target[i]);
	free(target);
}

char	**ft_argappend(char **args, char *cmd)
{
	char	**newargs;
	int		i;

	i = 0;
	while (args[i])
		i++;
	newargs = (char **)ft_calloc(i + 2, sizeof(char *));
	newargs[0] = ft_strdup(cmd);
	i = -1;
	while (args[++i])
		newargs[i + 1] = ft_strdup(args[i]);
	return (newargs);
}

char	*ft_strstrjoin(char *cmd, char *cmdpath)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(cmdpath, "/");
	ret = ft_strjoin(tmp, cmd);
	free(tmp);
	return (ret);
}

char	*ft_build_command(char *cmd, char *cmdpath)
{
	char	*ret;

	ret = NULL;
	if (ft_strchr(cmd, '/') || !cmdpath)
		ret = ft_strdup(cmd);
	else
		ret = ft_strstrjoin(cmd, cmdpath);
	return (ret);
}
