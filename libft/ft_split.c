/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 10:00:08 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/13 18:14:40 by aarcelia         ###   ########.fr       */
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

static char	**ft_dosplit(const char *s, int i, int words, char c)
{
	char	**ret;
	int		flag;

	ret = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	flag = -1;
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

char	**ft_split(char const *s, char c)
{
	int		words;

	if (!s)
		return (NULL);
	words = ft_wordcount(s, c);
	return (ft_dosplit(s, 0, words, c));
}
