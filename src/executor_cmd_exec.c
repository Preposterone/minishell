/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:51:43 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/12 20:19:43 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
**	if	cmd == '.' - print usage
		cmd refers to directory: 'say it's a directory'
		if envp->path is null == no such file or directory
*/
/*
static int ft_cmdpath_null(char *cmd, t_envp *envp)
{
	int ret;

	ret = 0;
	if (ft_strcmp(cmd, ".") == 0)
	{
		ft_puterr_arr((char *[]){cmd, MSH_DOT_1, MSH_DOT_2, NULL});
		ret = 2;
	}
	else if ((cmd[0] == '.' && ft_strcmp(cmd, "..") != 0 )|| cmd[0] == '/')
	{
		ft_puterrln("I dunno what to do atm");
		ret = 126;
	}
	else if (envp->sh_path == NULL)
	{
		ft_puterr_arr((char *[]){cmd, MSH_NO_SUCH_F_DIR, NULL});
		ret = 127;
	}
	exit(ret);
	(void)envp;
	// if (envp->ispipe)
	// return (ret);
} */

//if output_fd != -1, do dup2(output_fd, 1); close (output_fd);
int	executor(char **args, char *cmdpath, t_envp *envp,
				t_for_in_terminal *term_props)
{
	int		ret;
	char	*cmd_abs;
	char	**newargs;

	fprintf(stderr, "****\nRUNNING EXECUTOR WITH CMD: '%s', cmdpath: '%s'\n", args[0], cmdpath);
	ret = 0;
	if (!args[0])	//prevent segfault if no actual cmd is given
		ret = 0;
	else if (ft_isbuiltin(args[0]))
	{
		ret = ft_do_builtin(args[0], &args[1], envp, term_props); //do builtin
		exit (ret);
	}
	else
	{
		cmd_abs = ft_build_command(args[0], cmdpath);
		newargs = ft_argappend(&args[1], args[0]);
		if (execve(cmd_abs, newargs, envp->sh_envp) == -1)
			exit_minishell(args[0], MSH_CMD_NOT_FOUND, term_props);
	}
	return (ret);
}

int		ft_exec_cmd(t_for_in_parser **par, t_envp *sh_envp,
					t_for_in_terminal *term_props)
{
	char	*cmdpath;

	if (!(*par)->arguments[0])
	{
		close((*par)->output);
		close((*par)->input);
	}
	if ((*par)->output > 0 && (*par)->arguments[0])
	{
		dup2((*par)->output, 1);
		close((*par)->output);
	}
	if ((*par)->input > 0 && (*par)->arguments[0])
	{
		dup2((*par)->input, 0);
		close((*par)->input);
	}
	cmdpath = expander((*par)->arguments[0], sh_envp->sh_path);
	return (executor(
			&(*par)->arguments[0],        //args from cmdline
			cmdpath,                    //executable filepath
			sh_envp,                    //settings for shell
			term_props));				//props for exit (history)

}
