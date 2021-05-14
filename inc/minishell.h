/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:00:07 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/14 18:17:19 by aarcelia         ###   ########.fr       */
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
# include "error_management.h"
# include <stdio.h>

typedef struct s_all
{
	int			key_signal;
	int			exit_code;
	int			key_ctr;
	int			sh_lvl;
	int			max_depth;
}				t_all;

extern t_all	g_all;

#endif
