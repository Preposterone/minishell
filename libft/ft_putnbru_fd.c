/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 17:04:42 by aarcelia          #+#    #+#             */
/*   Updated: 2021/01/09 20:55:45 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_putnbru_fd(unsigned int n, int fd)
{
	char	s[ft_numlenu(n) + 1];
	int		i;
	int		mod;

	i = 0;
	mod = (n == 0);
	if (mod)
		return (ft_putnchar_fd('0', fd, 1));
	while (n)
	{
		s[i++] = (n % 10) + '0';
		n /= 10;
	}
	s[i] = '\0';
	return (ft_putstrr_fd(s, fd));
}
