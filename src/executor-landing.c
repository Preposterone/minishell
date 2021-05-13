/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor-landing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:56:29 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/13 13:26:19 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_fetch_exit_status(int status)
{
	if (status == 13)
		status -= 13;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (MSH_EXIT_SIGNAL + WTERMSIG(status));
	return (status);
}

static int ft_redirect_blt_in(t_for_in_parser **par, t_envp *sh_envp,
					  t_for_in_terminal *term_props)
{
	int ret;

	if ((*par)->output > 0)
	{
		dup2((*par)->output, 1);
		close((*par)->output);
	}
	if ((*par)->input > 0)
	{
		dup2((*par)->input, 0);
		close((*par)->input);
	}
	ret = ft_do_builtin((*par)->arguments[0], &(*par)->arguments[1], sh_envp, term_props);
	return (ret);
}
static int	ft_run_single(t_for_in_parser **par, t_envp *sh_envp,
					  t_for_in_terminal *term_props)
{
	int	ret;
	int	id;

	ret = 0;
	if (ft_isbuiltin((*par)->arguments[0]))
		ret = ft_redirect_blt_in(par, sh_envp, term_props);
	else
	{
		id = fork();
		if (id == -1)
			exit_fatal(MSH_FORK_EXIT);
		else if (id == 0)
			ret = ft_exec_cmd(par, sh_envp, term_props);
		else
			wait(&ret);
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

//TODO: case agnostic execution!
//TODO: '.' '/' = invoke stat (?)
//TODO: ; check for errorneos children

void	executor_secretary(t_for_in_parser **par, t_envp *sh_envp,
						t_for_in_terminal *term_props)
{
	int				i;
	int				num_cmds;
	t_pipe_data		pipe_data;
	int				status;

	status = 0;
	ft_update_last_arg(par, sh_envp);	//should this be done here?
	num_cmds = (*par)->key;
	if (num_cmds > 1)
	{
		ft_bzero(&pipe_data, sizeof(pipe_data));
		sh_envp->ispipe = 1;
		ft_run_pipes(par, sh_envp, term_props, &pipe_data);
		i = -1;
		while (++i < pipe_data.ch_total)	//wait for pipes here
			wait(&status);	//TODO: waitpid with exit status?

	}
	else
		status = ft_run_single(par, sh_envp, term_props);
	sh_envp->ispipe = 0;
	g_all.exit_code = ft_fetch_exit_status(status);
	dup2(sh_envp->truefd0, 0);
	dup2(sh_envp->truefd1, 1);
}
