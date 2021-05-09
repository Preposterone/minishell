/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:42:49 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 15:34:33 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_set(bool *sw, bool value)
{
	*sw = value;
	return (1);
}

void	ft_swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

void	*ft_safe_free(void *dst)
{
	if (dst)
		free(dst);
	return (NULL);
}

int	ft_bool_free(void *dst)
{
	if (dst)
		free(dst);
	return (1);
}
