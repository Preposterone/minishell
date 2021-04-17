/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:06:05 by aarcelia          #+#    #+#             */
/*   Updated: 2021/01/07 14:50:22 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	stopat;
	size_t	slen;
	size_t	retlen;
	char	*ret;
	int		i;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	retlen = (len >= slen - start) ? slen - start : len;
	if (!(ret = (char*)malloc(sizeof(char) * (retlen + 1))))
		return (NULL);
	stopat = (size_t)start + len;
	i = 0;
	while (start < stopat && s[start] && slen > start)
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}
