# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarcelia <aarcelia@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/27 16:31:52 by aarcelia          #+#    #+#              #
#    Updated: 2021/05/14 19:16:52 by aarcelia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEAD = ../inc/libft.h
INC_DIR = ../inc/.

SRCS =	ft_atoi.c	ft_isprint.c	ft_lstlast.c ft_memcpy.c	ft_split.c	ft_nputnbr_fd.c\
		ft_strmapi.c	ft_toupper.c	ft_bzero.c	ft_itoa.c	ft_lstmap.c	ft_putstrr_fd.c\
		ft_memmove.c	ft_strchr.c	ft_strncmp.c	ft_calloc.c	ft_strnstrchr.c ft_tointarr.c\
		ft_lstadd_back.c	ft_lstnew.c	ft_memset.c	ft_strdup.c	ft_strnstr.c	ft_isspace.c\
		ft_isalnum.c	ft_lstadd_front.c	ft_lstsize.c ft_putchar_fd.c	ft_putnchar.c	ft_strcmp_untill_c.c\
		ft_strjoin.c	ft_strrchr.c	ft_isalpha.c	ft_lstclear.c	ft_memcmpi.c ft_strcmpl.c\
		ft_memccpy.c	ft_putendl_fd.c	ft_strlcat.c	ft_strtrim.c ft_strndup.c	ft_atoll.c\
		ft_isascii.c	ft_lstdelone.c	ft_memchr.c	ft_putnbr_fd.c	ft_strstrchr.c	ft_math.c\
		ft_strlcpy.c	ft_substr.c	ft_isdigit.c	ft_lstiter.c	ft_memcmp.c	ft_utilities.c\
		ft_putstr_fd.c	ft_strlen.c	ft_tolower.c	ft_putstrn_fd.c	ft_strcmp.c	ft_putnbru_fd.c\
		ft_itoa_base.c	ft_numlen_base.c	ft_numlen.c	ft_memsetn.c	ft_utoa.c	ft_numlenu.c\

OBJS	=	${SRCS:.c=.o}

CC	= gcc
CFLAGS = -Wall -Werror -Wextra -o2

all:	${NAME}

.c.o:
	${CC} ${CFLAGS} -I ${INC_DIR} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
	@ar rc ${NAME} ${OBJS}
	@echo "LIBFT compiled"

clean:
			/bin/rm -f $(OBJS)

fclean:	clean
			/bin/rm -f $(NAME)

re:	fclean all

norm:
	@norminette ${SRCS} | grep --color -E '^|Error'

.PHONY:	all clean fclean re
