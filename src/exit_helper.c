/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:45:23 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/12 17:12:03 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//output into stderr: 'minishell: %s%s%s\n'
void	ft_puterr_arr(char *s[])
{
	int i;

	i = 0;
	ft_putstr_fd(MSH_MSG_GENERIC, 2);
	while (s[i])
		ft_putstr_fd(s[i++], 2);
	ft_putendl_fd("", 2);
}

//output into stderr: 'minishell: %s\n'
void	ft_puterrln(char *s)
{
	ft_putstr_fd(MSH_MSG_GENERIC, 2);
	ft_putendl_fd(s, 2);
}

// printf("%s%s\n", MSH_MSG_GENERIC, str);	//НУЖНО ПИСАТЬ ВО ВТОРОЙ ФД
	// ft_puterr_arr((char *[]){str, MSG_CMD_NOT_FOUND, NULL});
void	exit_minishell(char *str, int reason, t_for_in_terminal *t)
{
	del_settings_term(t);	//Восстанавливаем терминал
	if (reason == MSH_CMD_NOT_FOUND)
		ft_puterr_arr((char *[]){str, ": ", strerror(errno), NULL});
	else
		ft_puterrln(str);
	//
	exit(reason);
}

void	exit_fatal(int reason)
{
	ft_putstr_fd(MSH_FATAL_GEN, 2);
	if (reason == MSH_MALLOC_EXIT)
		ft_puterrln(MSH_MALLOC_ERR);
	else if (reason == MSH_FORK_EXIT)
		ft_puterrln(MSH_FORK_ERR);
	else if (reason == MSH_PIPE_EXIT)
		ft_puterrln(MSH_PIPE_ERR);
	exit(reason);
}
