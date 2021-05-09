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
#TODO: list .h files explicitly
H_FILES := $(shell find ./inc/ -type f -name "*.h" -exec basename {} \;)
HEADERS :=	$(addprefix $(INC_DIR)/, $(H_FILES))

#compiler setup
CC := gcc
CFLAGS += -Wall -Werror -Wextra -g3 #TODO: switch to o2
IFLAGS += -I$(INC_DIR)/

#Sources
#TODO: list sources explicitly
SRCS := $(shell find ./src/ -type f -name "*.c" -exec basename {} \;)
SRC_FILES := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
