/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 12:32:08 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/14 13:55:28 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Swaps position of strings in array (char**) */
static void	ft_char_ptr_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_quicksort_char_arr(char *arr[], uint length)
{
	uint	i;
	uint	piv;
	char	*key1;
	char	*key2;

	i = 0;
	piv = 0;
	if (length <= 1)
		return ;
	while (i < length)
	{
		key1 = ft_strndup(arr[i], ft_strchr_index(arr[i], '=') + 1);
		key2 = ft_strndup(arr[length -1], ft_strchr_index(arr[i], '=') + 1);
		if (ft_strcmp(key1, key2) < 0)
		{
			ft_char_ptr_swap(arr + i, arr + piv);
			piv++;
		}
		free(key1);
		free(key2);
		i++;
	}
	ft_char_ptr_swap(arr + piv, arr + length - 1);
	ft_quicksort_char_arr(arr, piv++);
	ft_quicksort_char_arr(arr + piv, length - piv);
}
