/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 15:27:04 by aarcelia          #+#    #+#             */
/*   Updated: 2021/02/09 11:44:21 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strstrchr(const char *str, const char **search)
{
	int	n;

	n = 0;
	if (!str)
		return (0);
	while (search[n])
	{
		if (ft_strcmp(str, search[n]) == 0)
			return (n);
		n++;
	}
	return (-1);
}

int	ft_strstrchr0(char *searchfor, const char **searchin, int upto)
{
	int	i;

	i = 0;
	if (!searchfor)
		return (0);
	while (upto)
	{
		i = 0;
		while (searchin[i])
		{
			if (ft_memcmp(searchfor, searchin[i], upto) == 0)
				return (i);
			i++;
		}
		upto--;
	}
	return (-1);
}

int	ft_strstrchr1(char *cmp, const char **cmpwith, int cmpchars)
{
	int	i;

	i = 0;
	if (!cmp)
		return (0);
	while (cmpwith[i])
	{
		if (ft_memcmp(cmp, cmpwith[i], cmpchars) == 0)
			return (i);
		i++;
	}
	return (-1);
}
