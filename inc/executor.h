/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:57:01 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/09 16:28:34 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"
# include <errno.h>
# include <sys/wait.h>

#ifndef LENCHECK
# define LENCHECK
#endif

/* **********************************HELPERS********************************* */

void	ft_freematrix(void **target);
char	**ft_argappend(char **args, char *cmd);
char	*ft_strstrjoin(char *cmd, char *cmdpath);
char	*ft_build_command(char *cmd, char *cmdpath);

/* **********************************FUNCTIONS******************************* */

void	executor_secretary(t_for_in_parser **par, t_envp *sh_envp,
						t_for_in_terminal *term_props);
int	executor_pipe(char **args, char *cmdpath, t_envp *envp,
					 t_for_in_terminal *term_props);
void	ft_exec_cmd_pipe(t_for_in_parser **par, t_envp *sh_envp,
						 t_for_in_terminal *term_props, t_pipe_data *pipe_data);

/* **********************************BUILTiINS******************************* */

int	ft_do_builtin(char *cmd, char **args, t_envp *envp,
			t_for_in_terminal *term_props);

int ft_do_exit(char **args, t_for_in_terminal *term_props);
int ft_do_env(char **args, char **envp_cpy);
int ft_do_unset(char **args, t_envp *sh_envp);
int ft_do_export(char **args, t_envp *sh_envp);
int ft_do_pwd(char **args);
int ft_do_cd(char **args, t_envp *env);
int	ft_do_echo(char **args);

/* **********************************BUILTiINS******************************* */

void	ft_print_arr(char **arr);
void	ft_add_to_envp(char **envp, char *add, t_envp *sh_envp);
/**
 * Operations with 'envp': Update key value, add if non-existant
 * @param key required syntax: "keyname="
 */
void	ft_update_envp_elem(char *key, char *value, t_envp *sh_envp);
/**
 * Operations with 'envp': Get value by key
 * @param key required syntax: "keyname="
 * @return allocated pointer to value
 */
char	*ft_get_envp_elem(char *key, t_envp *sh_envp);
/**
 * Operations with 'envp': Delete envp element identified by key
 * @param key required syntax: "keyname="
 * @return 1 for some reason
 */
int		ft_delete_envp_elem(char *key, t_envp *sh_envp);
#endif
