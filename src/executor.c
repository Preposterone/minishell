/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:56:29 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/07 11:41:26 by aarcelia         ###   ########.fr       */
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

//if output_fd != -1, do dup2(output_fd, 1); close (output_fd);
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
		id = fork();
		if (id)
			wait(&ret); //waitpid? WEXIT?
		else
		{
			if (execve(cmd_abs, newargs, envp->sh_envp) == -1)
			{
				ft_putendl_fd(cmd, 2);
				ft_putendl_fd("command not found", 2);
				exit(127);
			}
		}
		ft_freematrix((void **)newargs);
		free(cmd_abs);
		free(cmdpath);
	}
	return (ret);
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
	if (par[0]->key != 1)// || par[0]->previous->arguments)
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

//TODO: stuff for pipes,
//maybe think about remaking expander into substring replacement for PATH elements

int	executor_secretary(t_for_in_parser **par, t_envp *sh_envp,
						t_for_in_terminal *term_props)
{
	char	*cmdpath;
	int		i;

	ft_update_last_arg(par, sh_envp);	//should this be done here?
	// ft_putendl_fd(ft_get_envp_elem("_=", sh_envp), 1);	//print current last arg
	// ft_print_arr(sh_envp->sh_envp);	//print current envp

	// int output_fd =	open("out_file", O_CREAT | O_APPEND | O_RDWR, 00644);
	i = 0;
	while (i < (*par)->key)
	{
		if ((*par)->output > 0)
		{
			// replace stdout with output fd
			dup2((*par)->output, 1);
			close((*par)->output);
		}
		if ((*par)->input > 0)
		{
			// replace stdin with input fd
			dup2((*par)->input, 0);
			close((*par)->input);
		}
		cmdpath = expander(par[i]->arguments[0], sh_envp->sh_path);
		g_all.exit_code = executor(	par[i]->arguments[0],	//cmd
									&par[i]->arguments[1],	//args from cmdline
									cmdpath,				//executable filepath
									sh_envp,				//settings for shell
									term_props);			//props for exit (history)
		// restore stdin & stdout
		dup2(sh_envp->truefd0,0);
		dup2(sh_envp->truefd1,1);
		i++;
	}
	return (0);
}
