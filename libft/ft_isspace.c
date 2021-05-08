/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 11:11:35 by aarcelia          #+#    #+#             */
/*   Updated: 2021/01/29 11:14:31 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** space, form-feed ('\f'), newline ('\n'), carriage return ('\r'),
** horizontal tab ('\t'), and vertical tab ('\v').
*/

#include "libft.h"

int	ft_isspace(int c)
{
	return ((c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
			|| c == '\v'));
}
