/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:17:52 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 15:06:11 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	u_char	*pdst;
	u_char	*psrc;
	size_t	i;

	pdst = (u_char *)dst;
	psrc = (u_char *)src;
	i = 0;
	while (i < n)
	{
		*pdst = *psrc;
		if (*pdst == (u_char)c)
			return ((void *)dst + i + 1);
		pdst++;
		psrc++;
		i++;
	}
	return (NULL);
}
