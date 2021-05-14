/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:51:43 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/14 15:10:28 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft_puterr_arr((char *[]){"stat error: ", strerror(errno), NULL});
static bool	ft_is_path_dir(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1 && errno == ENOTDIR)
		exit_minishell(path, MSH_NOT_DIR, NULL);
	else if ((buf.st_mode & S_IFMT) == S_IFDIR)
		return (true);
	return (false);
}

static int	ft_validate_input(char **args, char *cmdpath, t_envp *envp,
				t_for_in_terminal *term_props)
{
	if (!args[0])
		exit(0);
	else if (!cmdpath && !ft_strchr(args[0], '/'))
		exit_minishell(args[0], MSH_CMD_NOT_FOUND, term_props);
	else if (ft_strcmp(args[0], ".") == 0)
		exit_minishell(args[0], MSH_DOT_EX, term_props);
	else if (ft_isbuiltin(args[0]))
		exit(ft_do_builtin(args[0], &args[1], envp, term_props));
	else if (ft_is_path_dir(args[0]))
		exit_minishell(args[0], MSH_IS_DIR_ERR, NULL);
	return (1);
}

// fprintf(stderr, "[EXECUTOR]: RUNNING CMD: '%s', cmdpath: '%s'\n", args[0],
// cmdpath);
// fprintf(stderr, "[EXECUTOR]: '/' found!\n");
/* this is ran inside a child*/
int	executor(char **args, char *cmdpath, t_envp *envp,
				t_for_in_terminal *term_props)
{
	int		ret;
	char	*cmd_abs;
	char	**newargs;

	ret = 0;
	if (ft_validate_input(args, cmdpath, envp, term_props))
	{
		cmd_abs = ft_build_command(args[0], cmdpath);
		newargs = ft_argappend(&args[1], args[0]);
		if (execve(cmd_abs, newargs, envp->sh_envp) == -1)
		{
			ft_puterr_arr((char *[]){args[0], ": ", strerror(errno), NULL});
			if (errno == EACCES)
				ret = 2;
			else
				ret = 1;
			exit(MSH_EXIT_SIGNAL - ret);
		}
	}
	return (ret);
}

//TODO: case agnostic execution!
int	ft_exec_cmd(t_for_in_parser **par, t_envp *sh_envp,
					t_for_in_terminal *term_props)
{
	char	*cmdpath;

	if (!(*par)->arguments[0] || !ft_strcmp("", (*par)->arguments[0]))
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
	if (ft_strcmp("", (*par)->arguments[0]))
		return (executor(&(*par)->arguments[0], cmdpath, sh_envp, term_props));
	else
		exit (0);
	return (0);
}
