#Setup variables
INC_DIR := ./inc
SRC_DIR := ./src
BIN_DIR := ./bin
LIB_DIR := $(BIN_DIR)/lib
OBJ_DIR := $(BIN_DIR)/obj
LFT_DIR := ./libft

OS_NAME := $(shell uname -s | tr A-Z a-z)

LFLAGS	:= -L$(LIB_DIR)/ -lft

ifeq ($(OS_NAME),darwin)	#OS_X
	LFLAGS += -ltermcap
	CFLAGS += -D LENCHECK='entry->d_namlen == len && '
else						#LINUX
	LFLAGS += -lncurses
	CFLAGS += -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-error=empty-body
endif

#Sources
H_FILES :=	error_management.h	expander.h	libft.h	minishell_structs.h \
			executor.h	gnl.h	minishell.h	termcap.h
HEADERS :=	$(addprefix $(INC_DIR)/, $(H_FILES))

#compiler setup
CC := gcc
CFLAGS += -Wall -Werror -Wextra -o2
IFLAGS += -I$(INC_DIR)/

#Sources
SRCS :=	builtin_cd.c	executor_cmd_exec.c	lexer_1.c	open.c	term_strjoin_for_line.c\
	builtin_exit.c	do_del_term.c	executor_helpers.c	lexer_2.c	term_dop.c\
	term_strjoin_for_mas.c	builtin_export.c	dollar.c	executor_pipe_setup.c\
	lexer_3.c	term_dop2.c	term_up_down_fun.c	builtin_export_sort.c	envp_ops_1.c\
	exit_helper.c	lexer_4_put_line_in_mas.c	term_gnl.c	term_work_with_file.c\
	builtins_env.c	envp_ops_2.c	expander.c	lexer_5.c	term_join.c	while_and_signal.c\
	bultins.c	executor-landing.c	lexer.c	main.c	term_main_fun.c	work_with_term.c
SRC_FILES := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
