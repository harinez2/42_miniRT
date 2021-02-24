CLONE_DIR	= minilibx-linux
MYRT_DIR	= minirt
GIT_URL		= https://github.com/42Paris/minilibx-linux
LIBNAME		= libmlx.a


all	: myrt

clone	:
	if [ ! -d "$(CLONE_DIR)" ]; then git clone $(GIT_URL); fi

$(PWD)/$(LIBNAME)	: clone
	cd "$(PWD)/$(CLONE_DIR)" && make
	cp "$(PWD)/$(CLONE_DIR)/$(LIBNAME)" "$(PWD)/$(MYRT_DIR)"

myrt	: $(PWD)/$(LIBNAME)
	cd "$(PWD)/$(MYRT_DIR)" && make

clean	:
	rm -rf $(CLONE_DIR)

fclean	: clean
	$(PWD)/$(LIBNAME)
