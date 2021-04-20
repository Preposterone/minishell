/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:47:08 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 15:12:27 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*ret;
	size_t	slen;

	slen = ft_strlen(s1) + 1;
	slen = ft_tern((n + 1 > slen), slen, n + 1);
	ret = malloc(sizeof(char) * slen);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, slen);
	return (ret);
}
