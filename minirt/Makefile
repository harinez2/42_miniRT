NAME		= miniRT
LIBNAME		= libmlx.a
CLONE_DIR	= ../minilibx-linux
INCLIB		= /usr/lib
INCLUDE		= -I./includes -I/usr/include -I$(CLONE_DIR)
SRC_DIR		= srcs
SRCS		= \
				gnl/get_next_line.c \
				gnl/get_next_line_utils.c \
				$(SRC_DIR)/ft_bitmap.c \
				$(SRC_DIR)/ft_errorclean.c \
				$(SRC_DIR)/ft_obj_cylinder.c \
				$(SRC_DIR)/ft_obj_plane.c \
				$(SRC_DIR)/ft_obj_sphere.c \
				$(SRC_DIR)/ft_obj_square.c \
				$(SRC_DIR)/ft_obj_triangle.c \
				$(SRC_DIR)/ft_raytracer.c \
				$(SRC_DIR)/ft_reader_file.c \
				$(SRC_DIR)/ft_reader_num.c \
				$(SRC_DIR)/ft_util_color.c \
				$(SRC_DIR)/ft_util_render.c \
				$(SRC_DIR)/ft_vec_op1.c \
				$(SRC_DIR)/ft_vec_op2.c \
				$(SRC_DIR)/ft_window.c \
				$(SRC_DIR)/main.c
OBJS		= $(SRCS:.c=.o)
CFLAGS		= -Wall -Werror -Wextra 
CCFLAGS_L	= -L$(CLONE_DIR) -L$(INCLIB) -lmlx -lXext -lX11 -lm -lbsd
CC			= gcc
RM			= rm -f


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(CCFLAGS_L) $(LIBNAME) -o $(NAME)

.c.o: $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDE) $(CCFLAGS_L) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
