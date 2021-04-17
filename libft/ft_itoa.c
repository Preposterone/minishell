/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:39:30 by aarcelia          #+#    #+#             */
/*   Updated: 2021/01/07 14:50:22 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	unsigned int	num;
	char			*ret;
	int				mod;
	int				i;
	int				numlen;

	i = 0;
	mod = n <= 0;
	num = mod ? -n : n;
	numlen = ft_numlen(n);
	if (!(ret = (char*)ft_calloc((numlen + mod + 1), sizeof(char))))
		return (NULL);
	if (mod)
		ret[i++] = n < 0 ? '-' : '0';
	while (num && numlen)
	{
		ret[--numlen + mod] = (num % 10) + '0';
		num /= 10;
		i++;
	}
	return (ret);
}
