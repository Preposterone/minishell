/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:14:50 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/13 18:14:51 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int64_t	ft_atoll(char *s)
{
	int64_t	ret;
	int		mod;
	int		i;
	int		len;

	ret = 0;
	i = 0;
	mod = 1;
	len = ft_strlen(s);
	if (len <= 19 || (s[0] == '-' && ft_strlen(&s[1]) <= 19))
	{
		if (s[0] == '-')
		{
			mod = -1;
			i = 1;
		}
		while (ft_isdigit(s[i]))
			ret = ret * 10 + s[i++] - '0';
	}
	return (ret * mod);
}
