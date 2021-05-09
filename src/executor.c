/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:56:29 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/09 12:56:06 by aarcelia         ###   ########.fr       */
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
	if (ft_strchr(cmd, '/') || !cmdpath)
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
	if (!cmd)	//prevent segfault if no actual cmd is given
		ret = 0;
	else if (ft_isbuiltin(cmd))
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


//if output_fd != -1, do dup2(output_fd, 1); close (output_fd);
int	executor_pipe(char *cmd, char **args, char *cmdpath, t_envp *envp,
			t_for_in_terminal *term_props)
{
	int		ret;
	char	*cmd_abs;
	char	**newargs;

	ret = 0;
	if (!cmd)	//prevent segfault if no actual cmd is given
		ret = 0;
	else if (ft_isbuiltin(cmd))
		ret = ft_do_builtin(cmd, args, envp, term_props); //do builtin
	else
	{
		cmd_abs = ft_build_command(cmd, cmdpath);
		newargs = ft_argappend(args, cmd);
		if (execve(cmd_abs, newargs, envp->sh_envp) == -1)
		{
			ft_putendl_fd(cmd, 2);
			ft_putendl_fd("command not found", 2);
			exit(127);
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
	if (par[0]->key != 1)
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

void	ft_close_all_pipes(int pipe[][2], int pipe_fd)
{
	int i;

	i = -1;
	while (++i < pipe_fd)
	{
		close(pipe[i][0]);
		close(pipe[i][1]);
	}
}

static void	ft_exec_cmd(t_for_in_parser **par, t_envp *sh_envp, t_for_in_terminal *term_props)
{
	char	*cmdpath;

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
	cmdpath = expander((*par)->arguments[0], sh_envp->sh_path);
	g_all.exit_code = executor(	(*par)->arguments[0],	//cmd
							&(*par)->arguments[1],		//args from cmdline
							cmdpath,					//executable filepath
							sh_envp,					//settings for shell
							term_props);				//props for exit (history)
	dup2(sh_envp->truefd0,0);
	dup2(sh_envp->truefd1,1);
}

void	ft_exec_cmd_pipe(t_for_in_parser **par, t_envp *sh_envp,
						t_for_in_terminal *term_props)
{
	char	*cmdpath;
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
/*
//child debug start
	fprintf(stderr, "****\nPipe data:\nchild index: '%d', pipe_fds[0]:'%d'[1]:'%d', cmd: '%s'\n"
	"Parsed OUT: '%d', Parsed IN: '%d'\n",
	pipe_data->ch_index, pipe_data->pipe_fd[pipe_data->ch_index][0],
	pipe_data->pipe_fd[pipe_data->ch_index][1], (*par)->arguments[0],
	(*par)->output, (*par)->input);
//child debug end
 */
	cmdpath = expander((*par)->arguments[0], sh_envp->sh_path);
	executor_pipe(	(*par)->arguments[0],	//cmd
							&(*par)->arguments[1],		//args from cmdline
							cmdpath,					//executable filepath
							sh_envp,					//settings for shell
							term_props);				//props for e	xit (history)

}

//TODO: actual error management
//maybe think about remaking expander into substring replacement for PATH elements

void	executor_secretary(t_for_in_parser **par, t_envp *sh_envp,
						t_for_in_terminal *term_props)
{
	int				i;
	int				num_cmds;
	t_pipe_data		pipe_data;
	t_for_in_parser *par_head;

	ft_update_last_arg(par, sh_envp);	//should this be done here?
	num_cmds = (*par)->key;
	if (num_cmds > 1)
	{
		i = -1;
		ft_bzero(&pipe_data, sizeof(pipe_data));
		while (++i < num_cmds)
		{
			if (pipe(pipe_data.pipe_fd[i]) == -1)
			{
				perror("PIPE FAILED");
				exit(112);
			}
		}
		par_head = (*par);

		while (par_head->key != 1)
			par_head = par_head->previous;	//move head to 1st parsed command
		pipe_data.ch_index = -1;
		while(++pipe_data.ch_index < num_cmds)
		{
			pipe_data.ch_id[pipe_data.ch_index] = fork();
			if (pipe_data.ch_id[pipe_data.ch_index] == -1)
			{
				perror("FORK FAILED");
				exit(111);
			}
			else if (pipe_data.ch_id[pipe_data.ch_index] == 0)
			{	//child code
				if (pipe_data.ch_index > 0)
					dup2(pipe_data.pipe_fd[pipe_data.ch_index - 1][0], 0);
				if (pipe_data.ch_index < num_cmds - 1)
					dup2(pipe_data.pipe_fd[pipe_data.ch_index][1], 1);
				else
					dup2(sh_envp->truefd1, STDOUT_FILENO);
				ft_close_all_pipes(pipe_data.pipe_fd, num_cmds);
				ft_exec_cmd_pipe(&par_head, sh_envp, term_props);
				exit(0);
			}
			else
				close(pipe_data.pipe_fd[pipe_data.ch_index][1]);
			par_head = par_head->next;
		}
		ft_close_all_pipes(pipe_data.pipe_fd, num_cmds);
		i = -1;
		while (++i < num_cmds)
			wait(NULL);	//TODO: waitpid with exit status?
		dup2(sh_envp->truefd0, 0);
		dup2(sh_envp->truefd1, 1);
	}
	else
		ft_exec_cmd(par, sh_envp, term_props);
}
