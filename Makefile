NAME		= miniRT
CLONE_DIR	= minilibx-linux
MYRT_DIR	= minirt
GIT_URL		= https://github.com/42Paris/minilibx-linux
LIBNAME		= libmlx.a


all: $(MYRT_DIR)/$(NAME)

$(CLONE_DIR):
	git clone $(GIT_URL)

$(MYRT_DIR)/$(LIBNAME): $(CLONE_DIR)
	make -C "$(PWD)/$(CLONE_DIR)"
	cp "$(PWD)/$(CLONE_DIR)/$(LIBNAME)" "$(PWD)/$(MYRT_DIR)"

$(MYRT_DIR)/$(NAME): $(MYRT_DIR)/$(LIBNAME)
	make -C "$(PWD)/$(MYRT_DIR)"

clean:
	rm -f "$(PWD)/$(MYRT_DIR)/$(LIBNAME)"
	cd "$(PWD)/$(MYRT_DIR)" && make fclean

fclean: clean
	rm -rf $(CLONE_DIR)

re: fclean all

.PHONY: all clean fclean re
