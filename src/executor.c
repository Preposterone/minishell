/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:56:29 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/23 16:16:56 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_argappend(char **args, char *cmd)
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
		newargs[i + 1] = args[i];
	// free(args); //is this needed?
	return (newargs);
}

static char	*ft_strstrjoin(char *cmd, char *cmdpath)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(cmdpath, "/");
	ret = ft_strjoin(tmp, cmd);
	free(tmp);
	return (ret);
}

int	executor(char *cmd, char **args, char *cmdpath, t_envp *envp)
{
	int		ret;
	char	*cmd_abs;
	char	**newargs;
	pid_t	child;

	ret = 0;
	(void )args;
	if (ft_isbuiltin(cmd))
		ret = ft_do_builtin(cmd, args);//do builtin
	else
	{
		cmd_abs = ft_strstrjoin(cmd, cmdpath);
		newargs = ft_argappend(args, cmd);
		child = fork(); //waitpid?
		wait(&ret);
		if (child == 0)
		{
			execve(cmd_abs, newargs, envp->sh_envp);
			exit(0); //should it be?
		}
	}
	return (ret);
}