/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:32:13 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/19 15:16:06 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	uint	num;
	char	s[12];
	int		i;

	i = 0;
	ft_bzero(s, 12);
	num = ft_abs(n);
	if (n < 0)
		ft_putchar_fd('-', fd);
	else if (!n)
		ft_putchar_fd('0', fd);
	while (num)
	{
		s[i++] = num % 10 + '0';
		num /= 10;
	}
	ft_putstrr_fd(s, fd);
}
