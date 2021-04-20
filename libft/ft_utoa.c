/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 18:51:40 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 15:39:14 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa(unsigned int n)
{
	char	*ret;
	int		mod;
	int		i;
	int		numlen;

	i = 0;
	mod = (!n);
	numlen = ft_numlenu(n);
	ret = (char *)ft_calloc((numlen + mod + 1), sizeof(char));
	if (!ret)
		return (NULL);
	if (mod)
		ret[i++] = '0';
	while (n && numlen)
	{
		ret[--numlen + mod] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	return (ret);
}
