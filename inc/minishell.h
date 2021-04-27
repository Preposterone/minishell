/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:00:07 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/23 14:12:52 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "minishell_structs.h"
# include "gnl.h"
# include "libft.h"
# include "termcap.h"
# include "expander.h"
# include "executor.h"
# include <stdio.h>
typedef struct	s_all
{
	//t_envp				sh_envp;	//copy of envp
	//t_for_in_terminal	termcap;	//struct for termcap
    int                     key_signal;
	int                     exit_code;
}				t_all;

extern t_all g_all;

#endif
