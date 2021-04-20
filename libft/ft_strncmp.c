/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:23:02 by aarcelia          #+#    #+#             */
/*   Updated: 2021/01/07 14:50:22 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	c1 = (unsigned char)*s1;
	c2 = (unsigned char)*s2;
	if (!n)
		return (0);
	while (c1 == c2 && n--)
	{
		c1 = (unsigned char)*s1++;
		c2 = (unsigned char)*s2++;
		if (!c1)
			return (c1 - c2);
	}
	return (c1 - c2);
}
