/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:56:29 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/09 16:31:41 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_run_single(t_for_in_parser **par, t_envp *sh_envp,
					  t_for_in_terminal *term_props)
{
	int	ret;
	int	id;

	ret = 0;
	if (ft_isbuiltin((*par)->arguments[0]))
		ret = ft_do_builtin((*par)->arguments[0], &(*par)->arguments[1], sh_envp, term_props);
	else
	{
		id = fork();
		if (id == -1)
			exit_fatal(MSH_FORK_EXIT);
		else if (id == 0)
			ft_exec_cmd(par, sh_envp, term_props);
		else
			wait(&ret);
	}
	g_all.exit_code = ret;
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

//TODO: actual error management

void	executor_secretary(t_for_in_parser **par, t_envp *sh_envp,
						t_for_in_terminal *term_props)
{
	int				i;
	int				num_cmds;
	t_pipe_data		pipe_data;

	ft_update_last_arg(par, sh_envp);	//should this be done here?
	num_cmds = (*par)->key;
	if (num_cmds > 1)
	{
		ft_bzero(&pipe_data, sizeof(pipe_data));
		ft_run_pipes(par, sh_envp, term_props, &pipe_data);
		i = -1;
		while (++i < pipe_data.ch_total)	//wait for pipes here
			wait(&g_all.exit_code);	//TODO: waitpid with exit status?
	}
	else
		ft_run_single(par, sh_envp, term_props);
	dup2(sh_envp->truefd0,0);
	dup2(sh_envp->truefd1,1);
}
