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

void	ft_freematrix(void **target)
{
	int i;

	i = -1;
	while (target[++i])
		free(target[i]);
	free(target);
}

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
		newargs[i + 1] = ft_strdup(args[i]);
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

static char *ft_build_command(char *cmd, char *cmdpath)
{
	char *ret;

	ret = NULL;
	if (ft_strchr(cmd, '/'))
		ret = ft_strdup(cmd);
	else
		ret = ft_strstrjoin(cmd, cmdpath);
	return (ret);
}

int	executor(char *cmd, char **args, char *cmdpath, t_envp *envp,
			t_for_in_terminal *term_props)
{
	int		ret;
	char	*cmd_abs;
	char	**newargs;
	pid_t	id;

	ret = 0;
	if (ft_isbuiltin(cmd))
		ret = ft_do_builtin(cmd, args, envp, term_props); //do builtin
	else
	{
		cmd_abs = ft_build_command(cmd, cmdpath);
		newargs = ft_argappend(args, cmd);
		id = fork(); //waitpid?
		if (id)
			wait(&ret);
		else
		{
			if (execve(cmd_abs, newargs, envp->sh_envp) == -1)
				ft_putendl_fd("command not found", 2);
			exit(0); //should it be?
		}
		ft_freematrix((void **)newargs);
		free(cmd_abs);
		free(cmdpath);
	}
	return (ret);
}

int	executor_secretary(t_for_in_parser **par, t_envp *sh_envp,
						t_for_in_terminal *term_props)
{
	char *cmdpath;

	if (par[0]->key == 1)
	{
		cmdpath = expander(par[0]->arguments[0], sh_envp->sh_path);
		g_all.exit_code = executor(par[0]->arguments[0], &par[0]->arguments[1], cmdpath, sh_envp, term_props);
	}
	return (0);
}
