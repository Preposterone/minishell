/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:45:23 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/29 11:51:31 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exit_minishell(char *str, int ex)
{
    printf("%s%s\n", MSH_MSG_GENERIC, str);
    exit(ex);
}
