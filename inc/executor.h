/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:57:01 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/23 18:37:46 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"

int	executor(char *cmd, char **args, char *cmdpath, t_envp *envp);
int	executor_secretary(t_for_in_parser **par, t_envp *sh_envp);

/*
	Builtin prototypes
*/

/**
 * Secretary function, switch-like
 */
int	ft_do_builtin(char *cmd, char **args); //need struct for output and input and pipe maybe?

int ft_do_exit(char **args);

int ft_do_set(char **args);

int ft_do_unset(char **args);

int ft_do_export(char **args);

int ft_do_pwd(char **args);

int ft_do_cd(char **args);

int	ft_do_echo(char **args);



#endif
