/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:00:35 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 15:11:15 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hasch(const char *s, char c)
{
	while (*s)
		if (*s++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		y;
	int		start;
	int		end;

	if (s1 == NULL)
		return (NULL);
	y = 0;
	end = ft_strlen(s1) - 1;
	start = 0;
	while (ft_hasch(set, s1[start]))
		start++;
	while (ft_hasch(set, s1[end]) && end > start)
		end--;
	ret = (char *)malloc((sizeof(char) * (end - start + 2)));
	if (!ret)
		return (NULL);
	while (start <= end)
		ret[y++] = s1[start++];
	ret[y] = '\0';
	return (ret);
}
