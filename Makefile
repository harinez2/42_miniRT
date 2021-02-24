NAME		= myrt
CLONE_DIR	= minilibx-linux
MYRT_DIR	= minirt
GIT_URL		= https://github.com/42Paris/minilibx-linux
LIBNAME		= libmlx.a


all: $(MYRT_DIR)/$(NAME)

$(CLONE_DIR):
	git clone $(GIT_URL)

$(MYRT_DIR)/$(LIBNAME): $(CLONE_DIR)
	cd "$(PWD)/$(CLONE_DIR)" && make
	cp "$(PWD)/$(CLONE_DIR)/$(LIBNAME)" "$(PWD)/$(MYRT_DIR)"

$(MYRT_DIR)/$(NAME): $(MYRT_DIR)/$(LIBNAME)
	cd "$(PWD)/$(MYRT_DIR)" && make

clean:

fclean: clean
	rm -rf $(CLONE_DIR)
	rm -f $(PWD)/$(MYRT_DIR)/$(LIBNAME)
	cd "$(PWD)/$(MYRT_DIR)" && make fclean

re: fclean all

.PHONY: all clean fclean re
