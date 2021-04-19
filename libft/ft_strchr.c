/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:14:20 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 14:50:08 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ret;
	char	ctmp;
	size_t	slen;

	slen = ft_strlen(s) + 1;
	ret = NULL;
	ctmp = (char)c;
	while (slen--)
	{
		if (*s == ctmp)
			return ((char *)s);
		s++;
	}
	return (ret);
}

int	ft_strchr_index(const char *s, int c)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (-1);
}
