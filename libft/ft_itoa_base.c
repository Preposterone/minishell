/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:14:05 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 15:37:58 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(unsigned long n, const char *base)
{
	char	*ret;
	int		numlen;
	size_t	baselen;

	numlen = (int)ft_numlen_base(n, base);
	baselen = ft_strlen(base);
	ret = (char *)ft_calloc((numlen + !n + 1), sizeof(char));
	if (!ret)
		return (NULL);
	if (!n)
		ret[numlen] = '0';
	while (numlen > 0)
	{
		ret[--numlen] = base[n % baselen];
		n /= baselen;
	}
	return (ret);
}
