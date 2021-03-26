NAME		= miniRT
LIBNAME		= libmlx.a
CLONE_DIR	= ../minilibx-linux
INCLIB		= /usr/lib
SRCS		= main.c \
		  ft_reader_file.c ft_reader_num.c \
		  ft_vec_op1.c ft_vec_op2.c \
		  ft_util_color.c ft_util_render.c \
		  ft_raytracer.c \
		  ft_obj_cylinder.c ft_obj_plane.c  ft_obj_sphere.c \
		  ft_obj_square.c  ft_obj_triangle.c \
		  ft_window.c ft_bitmap.c ft_errorclean.c \
		  ../gnl/get_next_line.c ../gnl/get_next_line_utils.c
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

