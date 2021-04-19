/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 11:19:52 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 15:37:08 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int		i;
	u_char	c1;
	u_char	c2;

	i = 0;
	c1 = (u_char)s1[i];
	c2 = (u_char)s2[i];
	while (c1 == c2)
	{
		if (!c1)
			return (c1 - c2);
		i++;
		c1 = (u_char)s1[i];
		c2 = (u_char)s2[i];
	}
	return (c1 - c2);
}
