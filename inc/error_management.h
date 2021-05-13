/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:46:03 by aarcelia          #+#    #+#             */
/*   Updated: 2021/05/13 12:10:00 by aarcelia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MANAGEMENT_H
# define ERROR_MANAGEMENT_H
# include <stdio.h>

/* **********************************FUNCTIONS******************************* */

void	exit_fatal(int reason);
void	ft_puterrln(char *s);
void	ft_puterr_arr(char *s[]);

/* **********************************MESSAGES******************************** */

# define MSH_MSG_GENERIC "minishell: "
# define MSH_EXT_ARGS "too many arguments"
# define MSH_EXT_NUMER "numeric argument required"
# define CANT_OPEN_FILE "could not open the file"
# define FILE_DONT_REAL "No such file or directory"
# define RED_WHERE "syntax error near unexpected token `newline'"
# define RED_WHERE "syntax error near unexpected token `newline'"
# define M_QUOTES "The quotes are not closed"
# define ERROR_E "Error"
# define MSG_CMD_NOT_FOUND ": command not found"
# define MSH_ID_INV "': not a valid identifier"
# define EXITT "exit"
# define MSH_NO_SUCH_F_DIR ": no such file or directory"

/* *************************EXECUTOR_ERR_MSGS******************************** */
# define MSH_DOT_1 ": filename argument required\n"
# define MSH_DOT_2 ".: usage: . filename [arguments]"
# define MSH_IS_DIR ": is a directory"
# define MSH_PERM_DENIED ": Permission denied"

/* *******************************ERROR_CODES******************************** */

# define MSH_EXIT_SUCCESS 0
# define MSH_EXIT_FAIL 1
# define MSH_CMD_NOT_FOUND 127

/* ******************************FATAL_ERR_MSG******************************* */
# define MSH_FATAL_GEN "\x1b[31mFATAL! \x1b[0m"
# define MSH_MALLOC_ERR "malloc: failed! Exiting."
# define MSH_FORK_ERR "fork: failed! Exiting."
# define MSH_PIPE_ERR "pipe: failed! Exiting."

/* *****************************FATAL_ERR_CODE******************************* */
# define MSH_MALLOC_EXIT	111
# define MSH_FORK_EXIT		112
# define MSH_PIPE_EXIT		113
# define MSH_EXIT_SIGNAL	128

#endif
