NAME		= miniRT
LIBNAME		= libmlx.a
CLONE_DIR	= ../minilibx-linux
INCLIB		= /usr/lib
INCLUDE		= -I./includes -I/usr/include -I$(CLONE_DIR)
SRC_DIR		= srcs
SRCS		= \
				gnl/get_next_line.c \
				gnl/get_next_line_utils.c \
				$(SRC_DIR)/error_clean.c \
				$(SRC_DIR)/lib_ft.c \
				$(SRC_DIR)/main.c \
				$(SRC_DIR)/obj_cone_getdistance.c \
				$(SRC_DIR)/obj_cone.c \
				$(SRC_DIR)/obj_cylinder.c \
				$(SRC_DIR)/obj_plane.c \
				$(SRC_DIR)/obj_sphere.c \
				$(SRC_DIR)/obj_square.c \
				$(SRC_DIR)/obj_triangle.c \
				$(SRC_DIR)/obj_util.c \
				$(SRC_DIR)/output_bitmap.c \
				$(SRC_DIR)/output_screen.c \
				$(SRC_DIR)/output_window.c \
				$(SRC_DIR)/output_window_handler.c \
				$(SRC_DIR)/raytracer.c \
				$(SRC_DIR)/readfile.c \
				$(SRC_DIR)/readfile_config.c \
				$(SRC_DIR)/readfile_num.c \
				$(SRC_DIR)/readfile_objs.c \
				$(SRC_DIR)/readfile_objs2d.c \
				$(SRC_DIR)/util_color.c \
				$(SRC_DIR)/util_print_m.c \
				$(SRC_DIR)/util_print_m_objs.c \
				$(SRC_DIR)/util_print_m_objs2d.c \
				$(SRC_DIR)/util_render.c \
				$(SRC_DIR)/util_vector.c \
				$(SRC_DIR)/util_vector_calc.c \
				$(SRC_DIR)/util_vector_calcprod.c \
				$(SRC_DIR)/util_vector_normalize.c
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
