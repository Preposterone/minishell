/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:39:04 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/21 12:31:45 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "minishell.h"
# include <dirent.h>

# define BLT_IN (char *[]){"echo","cd","pwd","export","unset","set","exit",NULL}

typedef struct	s_envp
{
	char	**sh_envp;	//malloc, for set / unset
	char	*sh_path;	//malloc, for executor logic
}				t_envp;

# define ERR_CMD_NOT_FOUND ": command not found"

void	ft_envp_cpy(const char *envp[], t_envp *buf);
char	*expander(char *cmd, char *path);


#endif
