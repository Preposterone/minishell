#Setup variables
INC_DIR := ./inc
SRC_DIR := ./src
BIN_DIR := ./bin
LIB_DIR := $(BIN_DIR)/lib
OBJ_DIR := $(BIN_DIR)/obj
LFT_DIR := ./libft

OS_NAME := $(shell uname -s | tr A-Z a-z)

LFLAGS	:= -L$(LIB_DIR)/ -lft 

endif
#TODO: list .h files explicitly
H_FILES := $(shell find ./inc/ -type f -name "*.h" -exec basename {} \;)
HEADERS :=	$(addprefix $(INC_DIR)/, $(H_FILES))

#compiler setup
CC := gcc
CFLAGS += -Wall -Werror -Wextra $(KEYMAP) -g3 #todo: switch to o2
IFLAGS += -I/usr/include -I$(INC_DIR)/ -I$(MLX_DIR)/

#Sources
#TODO: list sources explicitly
SRCS := $(shell find ./src/ -type f -name "*.c" -exec basename {} \;)

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
