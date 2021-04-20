/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nputnbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:41:03 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 14:42:03 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nputnbr_fd(int n, int fd)
{
	unsigned int	num;
	char			s[12];
	int				i;
	int				mod;

	i = 0;
	mod = (n <= 0);
	ft_bzero(s, 12);
	num = ft_abs(n);
	if (mod && n < 0)
		ft_putchar_fd('-', fd);
	else if (mod && !n)
		ft_putchar_fd('0', fd);
	while (num)
	{
		s[i++] = num % 10 + '0';
		num /= 10;
	}
	return (ft_putstrr_fd(s, fd) + mod);
}
