/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmpi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 13:00:56 by aarcelia          #+#    #+#             */
/*   Updated: 2021/01/07 14:50:22 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmpi(const void *s1, const void *s2, size_t n)
{
	unsigned char c1;
	unsigned char c2;

	if (n == 0)
		return (0);
	while (n--)
	{
		c1 = tolower(*(unsigned char*)s1);
		c2 = tolower(*(unsigned char*)s2);
		if (c1 != c2)
			return (c1 - c2);
		s1++;
		s2++;
	}
	return (c1 - c2);
}
