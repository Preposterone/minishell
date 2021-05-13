/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmpl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:24:02 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/13 17:34:22 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmpl(const char *s1, const char *s2)
{
	int		i;
	u_char	c1;
	u_char	c2;

	i = 0;
	c1 = ft_tolower((u_char)s1[i]);
	c2 = ft_tolower((u_char)s2[i]);
	while (c1 == c2)
	{
		if (!c1)
			return (c1 - c2);
		i++;
		c1 = ft_tolower((u_char)s1[i]);
		c2 = ft_tolower((u_char)s2[i]);
	}
	return (c1 - c2);
}
