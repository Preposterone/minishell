/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:39:04 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/23 14:35:00 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include <dirent.h>

# define BLT_IN (char *[]){"echo","cd","pwd","export","unset","env","exit",NULL}
//# define ERR_CMD_NOT_FOUND ": command not found"

void	ft_envp_cpy(const char *envp[], t_envp *buf);
bool	ft_isbuiltin(char *cmd);
char	*expander(char *cmd, char *path);

#endif
