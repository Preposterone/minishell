/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:51:14 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 14:58:51 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	findlen;
	char	*dst;
	char	*find;
	int		i;

	if (!haystack && !needle)
		return (NULL);
	dst = (char *)haystack;
	find = (char *)needle;
	i = 0;
	findlen = ft_strlen(find);
	if (!findlen)
		return (dst);
	while (dst[i] && len)
	{
		if (dst[i] == *find && findlen <= len)
			if (!ft_strncmp(&dst[i], find, findlen))
				return (&dst[i]);
		i++;
		len = ft_tern((len == 0), 0, len - 1);
	}
	return (NULL);
}
