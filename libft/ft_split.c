/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 10:00:08 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 17:08:22 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char const *s, char c)
{
	int	words;

	words = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c)
			words++;
		while (*s != c && *s + 1 && *s)
			s++;
		if (*s)
			s++;
	}
	return (words);
}

/*
** iterate through s until c encountered; return ptr to malloc'd word
*/

static char	*ft_wordmalloc(const char *s, char c)
{
	char	*ret;
	int		y;

	y = 0;
	while (s[y] != c && s[y])
		y++;
	ret = (char *)ft_calloc(y + 1, sizeof(char));
	if (!ret)
		return (NULL);
	y = 0;
	while (*s != c && *s)
		ret[y++] = (char)*s++;
	return (ret);
}

static char	**ft_freeall(char **s, int i)
{
	while (i >= 0)
		free(s[i--]);
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		words;
	int		flag;
	int		i;

	i = 0;
	flag = -1;
	if (!s)
		return (NULL);
	words = ft_wordcount(s, c);
	ret = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (*s && i <= words - 1)
	{
		if (flag >= 0)
			s++;
		flag = 0;
		if (*s != c && words)
		{
			ret[i] = ft_wordmalloc(s, c);
			if (!(ret[i]))
				return (ft_freeall(ret, i));
			i++;
		}
		while (*s != c && *s + 1 && *s)
			s++;
	}
	return (ret);
}
