/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_untill_c.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 12:42:13 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/14 13:53:54 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_untill_c(const char *s1, const char *s2, char c)
{
	int		i;
	u_char	c1;
	u_char	c2;

	i = 0;
	c1 = (u_char)s1[i];
	c2 = (u_char)s2[i];
	while (c1 == c2 && c1 != c && c2 != c)
	{
		if (!c1)
			return (c1 - c2);
		i++;
		c1 = (u_char)s1[i];
		c2 = (u_char)s2[i];
	}
	return (c1 - c2);
}
