NAME := minishell

include variables.mk

#default make target
all: $(NAME)

#compilation
$(OBJS):  $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o ${<$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c} $@
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o ${<$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c} $@

#main targets
$(NAME): $(OBJS)
	@$(MAKE) -j 6 -C $(LFT_DIR)/
	@cp $(LFT_DIR)/libft.a $(LIB_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJS) $(LFLAGS)

re:	fclean all

#cleaning up
cleanlib:
	/bin/rm -f $(LIB_DIR)/*
clean:
	@make clean -C $(MLX_DIR)
	@make clean -C $(LFT_DIR)
	/bin/rm -f $(OBJS)
fclean:	clean cleanlib
	@make fclean -C $(LFT_DIR)
	/bin/rm -f libmlx.dylib
	/bin/rm -f $(NAME)
cleanall: fclean dclean

#debug section
dclean:
	/bin/rm -rf 'a.out.dSYM'
	/bin/rm -f 'a.out'
debugsetup: dclean
	@tput clear && tput bold && tput setaf 1
	@echo "*********BEGIN DEBUG*********"
	@tput sgr 0

a.out:
	$(CC) $(CFLAGS) $(IFLAGS) $(addprefix $(SRC_DIR)/, $(SRCS)) $(LFLAGS)

debug: a.out

#extra
norm:
	@make norm -C $(LFT_DIR)
	@norminette ${SRC_DIR}/. | grep --color -E '^|Error'

norminc:
	@norminette ${INC_DIR}/. | grep --color -E '^|Error'

#shortcuts
s: stats
ca: cleanall
n: norm norminc
c: commit
r: run

.PHONY:	all clean fclean re
