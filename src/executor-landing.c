/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor-landing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:56:29 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/14 20:25:04 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_fetch_exit_status(int status, t_envp *sh_envp)
{
	char	*val;

	if (g_all.sh_lvl != g_all.max_depth)
	{
		g_all.max_depth--;
		val = ft_itoa(g_all.max_depth);
		ft_update_envp_elem("SHLVL=", val, sh_envp);
		free(val);
	}
	if (status == 13)
		status -= 13;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status) && !sh_envp->isb_in)
		return (MSH_EXIT_SIGNAL + WTERMSIG(status));
	return (status);
}

static int	ft_redirect_blt_in(t_for_in_parser **par, t_envp *sh_envp,
					  t_for_in_terminal *term_props)
{
	int	ret;

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
	ret = ft_do_builtin((*par)->arguments[0], \
		&(*par)->arguments[1], sh_envp, term_props);
	return (ret);
}

static int	ft_run_single(t_for_in_parser **par, t_envp *sh_envp,
					  t_for_in_terminal *term_props)
{
	int	ret;
	int	id;

	ret = 0;
	if (ft_isbuiltin((*par)->arguments[0]))
	{
		sh_envp->isb_in = 1;
		ret = ft_redirect_blt_in(par, sh_envp, term_props);
	}
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

/*
	fprintf(stderr, "EXECNAME '%s'\n", exec);
	fprintf(stderr, "Running EXECNAME '%s'\n", exec);
 */

static void	ft_check_for_execname(char *cmd, char *exec, t_envp *sh_envp)
{
	char	*tmp;
	char	*val;

	tmp = ft_strjoin("./", exec);
	if (cmd)
	{
		if (!ft_strcmp(cmd, tmp) || (ft_strrchr(cmd, '/')
				&& cmd[ft_strlen(cmd)] != '/'
				&& ft_strlen(cmd) > ft_strlen(exec)
				&& !ft_strcmp(ft_strrchr(cmd, '/'), exec))
			|| (!sh_envp->sh_path && !ft_strcmp(cmd, exec)))
		{
			g_all.max_depth = g_all.sh_lvl + 1;
			val = ft_itoa(g_all.max_depth);
			ft_update_envp_elem("SHLVL=", val, sh_envp);
			free(val);
		}
	}
	free(tmp);
}

void	executor_secretary(t_for_in_parser **par, t_envp *sh_envp,
						t_for_in_terminal *term_props)
{
	int				i;
	int				num_cmds;
	t_pipe_data		pipe_data;
	int				status;

	status = 0;
	ft_update_last_arg(par, sh_envp);
	num_cmds = (*par)->key;
	ft_check_for_execname((*par)->arguments[0], sh_envp->sh_name, sh_envp);
	if (num_cmds > 1)
	{
		ft_bzero(&pipe_data, sizeof(pipe_data));
		sh_envp->ispipe = 1;
		ft_run_pipes(par, sh_envp, term_props, &pipe_data);
		i = -1;
		while (++i < pipe_data.ch_total)
			wait(&status);
	}
	else
		status = ft_run_single(par, sh_envp, term_props);
	g_all.exit_code = ft_fetch_exit_status(status, sh_envp);
	sh_envp->ispipe = 0;
	sh_envp->isb_in = 0;
	dup2(sh_envp->truefd0, 0);
	dup2(sh_envp->truefd1, 1);
}
