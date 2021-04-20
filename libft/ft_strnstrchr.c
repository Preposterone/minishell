/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstrchr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 18:41:01 by aarcelia          #+#    #+#             */
/*   Updated: 2021/01/07 14:50:22 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Searches for str in search, but checks no more than n characters
** returns 1 if str found, else 0
*/

int	ft_strnstrchr(const char *str, const char **search, size_t n)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (search[i])
	{
		if (ft_strnstr(search[i], str, n) == 0)
			return (1);
		i++;
	}
	return (0);
}
