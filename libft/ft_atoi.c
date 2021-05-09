/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:18:40 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/18 17:26:33 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long int	ret;
	int				mod;

	ret = 0;
	mod = 1;
	while (ft_isspace((char)*str))
		str++;
	if ((char)*str == '-')
	{
		mod = -1;
		str++;
	}
	else if ((char)*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		if (ret * mod < -2147483648)
			return (0);
		else if (ret * mod > 2147483647)
			return (-1);
		ret = ret * 10 + ((char)*str++ - '0');
	}
	return ((int)ret * mod);
}
