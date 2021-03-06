/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlenu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 16:11:01 by aarcelia          #+#    #+#             */
/*   Updated: 2021/01/09 16:11:01 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlenu(unsigned int n)
{
	int	nret;

	nret = 0;
	while (n)
	{
		n /= 10;
		nret++;
	}
	return (nret);
}
