/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tointarr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 10:19:33 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 14:52:08 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen_isdigit(const char *s)
{
	int	ret;

	ret = 0;
	while (ft_isdigit(s[ret]))
		ret++;
	return (ret);
}

int	*ft_tointarr(const char *s, int len)
{
	int	*ret;
	int	i;

	i = -1;
	ret = (int *)ft_calloc(len, sizeof(int));
	if (!ret || ft_strlen_isdigit(s) != len)
		return (NULL);
	while (ft_isdigit(s[++i]))
		ret[i] = s[i] - '0';
	return (ret);
}

int	*ft_tointarr_substitute(char *s, char *sub_chr, int *int_arr)
{
	int	i;
	int	y;
	int	len;

	i = 0;
	len = ft_strlen(s);
	if (len == 0 || ft_strlen(sub_chr) == 0)
		return (NULL);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
		{
			y = ft_strchr_index(sub_chr, s[i]);
			if (y >= 0)
				s[i] = int_arr[y] + '0';
			else
				return (NULL);
		}
		i++;
	}
	if (i == len)
		return (ft_tointarr(s, len));
	return (NULL);
}
