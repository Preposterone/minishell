NAME := minishell

include variables.mk

#default make target
all: $(NAME)

#compilation
$(OBJS):  $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o ${<$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c} $@
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o ${<$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c} $@

#main recipes
$(NAME): $(OBJS)
	@$(MAKE) -j 6 -C $(LFT_DIR)/
	@mv $(LFT_DIR)/libft.a $(LIB_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJS) $(LFLAGS)
	@echo ${NAME} compiled

re:	fclean all

#cleaning up
cleanlib:
	/bin/rm -f $(LIB_DIR)/*.a

clean:
	@make clean -C $(LFT_DIR)
	/bin/rm -f $(OBJS)

fclean:	clean cleanlib
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
	$(CC) $(CFLAGS) $(IFLAGS) $(SRC_FILES) $(LFLAGS)

debug: a.out

#extra
norm:
	@make norm -C $(LFT_DIR)
	@norminette ${SRC_FILES} | grep --color -E '^|Error'

norminc:
	@norminette ${HEADERS} | grep --color -E '^|Error'

#shortcuts
ca: cleanall
n: norm norminc

.PHONY:	all clean fclean re
