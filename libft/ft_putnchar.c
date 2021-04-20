/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 18:49:36 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 15:01:57 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnchar_fd(char c, int fd, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		write(fd, &c, sizeof(char));
		i++;
	}
	return ((size_t)i);
}
