

#include "minishell.h"

static void	ft_close_all_pipes(int pipe[][2], int pipe_fd)
{
	int	i;

	i = -1;
	while (++i < pipe_fd)
	{
		close(pipe[i][0]);
		close(pipe[i][1]);
	}
}

static void	ft_generate_pipes(t_pipe_data *pipe_data)
{
	int	i;

	i = -1;

	while (++i < pipe_data->ch_total)
	{
		if (pipe(pipe_data->pipe_fd[i]) == -1)
			exit_fatal(MSH_PIPE_EXIT);
	}
}

static void	ft_connect_pipes(t_pipe_data *pipe_data, t_envp *sh_envp)
{
	if (pipe_data->ch_index > 0)
		dup2(pipe_data->pipe_fd[pipe_data->ch_index - 1][0], 0);
	if (pipe_data->ch_index < pipe_data->ch_total - 1)
		dup2(pipe_data->pipe_fd[pipe_data->ch_index][1], 1);
	else
		dup2(sh_envp->truefd1, STDOUT_FILENO);
}

void	ft_run_pipes(t_for_in_parser **par, t_envp *sh_envp,
					 t_for_in_terminal *term_props, t_pipe_data *pipe_data)
{
	t_for_in_parser *par_head;

	pipe_data->ch_total = (*par)->key;
	par_head = (*par);
	ft_generate_pipes(pipe_data);
	while (par_head->key != 1)
		par_head = par_head->previous;
	pipe_data->ch_index = -1;
	while(++pipe_data->ch_index < pipe_data->ch_total)
	{
		pipe_data->ch_id[pipe_data->ch_index] = fork();
		if (pipe_data->ch_id[pipe_data->ch_index] == -1)
			exit_fatal(MSH_FORK_EXIT);
		else if (pipe_data->ch_id[pipe_data->ch_index] == 0)
		{
			ft_connect_pipes(pipe_data, sh_envp);
			ft_close_all_pipes(pipe_data->pipe_fd, pipe_data->ch_total);
			ft_exec_cmd(&par_head, sh_envp, term_props);
		}
		else
			close(pipe_data->pipe_fd[pipe_data->ch_index][1]);
		par_head = par_head->next;
	}
	ft_close_all_pipes(pipe_data->pipe_fd, pipe_data->ch_total);
}
