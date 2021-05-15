/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:28:22 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/14 19:44:26 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	ret = malloc(count * size);
	if (!ret)
		exit_fatal(MSH_MALLOC_EXIT);
	return (ft_memset(ret, 0, count * size));
}
