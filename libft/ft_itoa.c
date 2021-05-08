/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:39:30 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 14:45:57 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	unsigned int	num;
	char			*ret;
	int				mod;
	int				i;
	int				numlen;

	i = 0;
	mod = n <= 0;
	num = ft_abs(n);
	numlen = ft_numlen(n);
	ret = (char *)ft_calloc((numlen + mod + 1), sizeof(char));
	if (!ret)
		return (NULL);
	if (mod && n < 0)
		ret[i++] = '-';
	else if (mod && !n)
		ret[i++] = '0';
	while (num && numlen)
	{
		ret[--numlen + mod] = (num % 10) + '0';
		num /= 10;
		i++;
	}
	return (ret);
}
