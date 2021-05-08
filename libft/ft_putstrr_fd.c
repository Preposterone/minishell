/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:48:47 by aarcelia          #+#    #+#             */
/*   Updated: 2021/01/09 20:55:45 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putstrr_fd(char *s, int fd)
{
	size_t	n;
	int		i;

	n = ft_strlen(s);
	i = n;
	while (i >= 0)
	{
		if (s[i])
			ft_putchar_fd(s[i], fd);
		i--;
	}
	return (n);
}
