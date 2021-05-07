/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:46:03 by aarcelia          #+#    #+#             */
/*   Updated: 2021/04/29 12:38:46 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MANAGEMENT_H
# define ERROR_MANAGEMENT_H
# include <stdio.h>
/* **********************************MESSAGES******************************** */

# define MSH_MSG_GENERIC "minishell: "
# define MSH_MSG_TOO_MANY_ARGS "too many arguments"
# define MSH_MSG_EXIT_NUMERIC "numeric argument required"
# define CANT_OPEN_FILE "could not open the file"
# define FILE_DONT_REAL "No such file or directory"
# define RED_WHERE "syntax error near unexpected token `newline'"
# define RED_WHERE "syntax error near unexpected token `newline'"
# define M_QUOTES "The quotes are not closed"
# define ERROR_E "Error"

/* *******************************ERROR_CODES******************************** */

# define MSH_EXIT_SUCCESS 0
# define MSH_EXIT_FAIL 1

#endif
