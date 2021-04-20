/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 17:04:42 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 15:37:41 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbru_fd(unsigned int n, int fd)
{
	char	s[12];
	int		i;
	int		mod;

	i = 0;
	mod = (n == 0);
	ft_bzero(s, 12);
	if (mod)
		return (ft_putnchar_fd('0', fd, 1));
	while (n)
	{
		s[i++] = (n % 10) + '0';
		n /= 10;
	}
	return (ft_putstrr_fd(s, fd));
}
