/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:39:04 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/10 17:22:00 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include <dirent.h>

void	ft_envp_cpy(const char *envp[], t_envp *buf);
bool	ft_isbuiltin(char *cmd);
char	*expander(char *cmd, char *path);

#endif
