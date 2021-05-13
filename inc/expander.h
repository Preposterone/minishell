/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:39:04 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/13 12:56:58 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include <dirent.h>
# include <sys/stat.h>

void	ft_envp_cpy(const char *envp[], t_envp *buf);
bool	ft_isbuiltin(char *cmd);
char	*expander(char *cmd, char *path);

#endif
