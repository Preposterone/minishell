/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:44:09 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 15:17:16 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	i = 0;
	if (dstsize == 0 || dst == NULL || src == NULL)
		return (ft_tern(src == NULL, 0, ft_strlen(src)));
	srclen = ft_strlen(src);
	while (--dstsize && *src)
	{
		*dst++ = *src++;
		i++;
	}
	*dst = '\0';
	return (ft_tern(i < srclen, srclen, i));
}
