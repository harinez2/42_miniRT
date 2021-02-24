CLONE_DIR	= minilibx-linux
MYRT_DIR	= minirt
GIT_URL		= https://github.com/42Paris/minilibx-linux
LIBNAME		= libmlx.a


all	: myrt

clone	:
	if [ ! -d "$(CLONE_DIR)" ]; then git clone $(GIT_URL); fi

$(MYRT_DIR)/$(LIBNAME)	: clone
	cd "$(PWD)/$(CLONE_DIR)" && make
	cp "$(PWD)/$(CLONE_DIR)/$(LIBNAME)" "$(PWD)/$(MYRT_DIR)"

myrt	: $(MYRT_DIR)/$(LIBNAME)
	cd "$(PWD)/$(MYRT_DIR)" && make

clean	:

fclean	: clean
	rm -rf $(CLONE_DIR)
	rm -f $(PWD)/$(MYRT_DIR)/$(LIBNAME)
