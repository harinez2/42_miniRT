NAME		= miniRT
LIBNAME		= libmlx.a
CLONE_DIR	= ../minilibx-linux
INCLIB		= /usr/lib
SRCS		= main.c ../gnl/get_next_line.c ../gnl/get_next_line_utils.c
OBJS		= $(SRCS:.c=.o)
CCFLAGS_I	= -Wall -Werror -Wextra -I/usr/include -I$(CLONE_DIR)
CCFLAGS_L	= -L$(CLONE_DIR) -L$(INCLIB) -lmlx -lXext -lX11 -lm -lbsd
CC		= gcc
RM		= rm -f


$(NAME): $(SRCS)
	$(CC) $(CCFLAGS_I) $(SRCS) $(CCFLAGS_L) $(LIBNAME) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

