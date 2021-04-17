/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:32:13 by aarcelia          #+#    #+#             */
/*   Updated: 2021/01/07 14:50:22 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;
	char			s[ft_numlen(n) + 1];
	int				i;
	int				mod;

	i = 0;
	mod = (n <= 0);
	num = n < 0 ? -n : n;
	if (mod)
		ft_putchar_fd(n < 0 ? '-' : '0', fd);
	while (num)
	{
		s[i++] = num % 10 + '0';
		num /= 10;
	}
	s[i] = '\0';
	ft_putstrr_fd(s, fd);
}
