/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:39:39 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 14:53:57 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	slen;

	slen = ft_strlen(s1) + 1;
	ret = malloc(sizeof(char) * slen);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, slen);
	return (ret);
}
