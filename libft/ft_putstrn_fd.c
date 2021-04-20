/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrn_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:26:23 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 15:36:25 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putstrn_fd(const char *s, int fd, int n)
{
	int	bytes;
	int	len;

	len = (int)ft_strlen(s);
	bytes = ft_tern(len > n, n, len);
	if (s)
		write(fd, s, bytes);
	return (bytes);
}
