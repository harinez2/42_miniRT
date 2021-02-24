NAME		= myrt
LIBNAME		= libmlx.a
CLONE_DIR	= minilibx-linux
INCLIB		=/usr/lib
SRCS		= main.c
OBJS		= ${SRCS:.c=.o}
CCFLAGS		= -Wall -Werror -Wextra -L../$(CLONE_DIR) -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd
CC			= gcc
RM		= rm -f


${OBJS}:
	${CC} ${CCFLAGS} ${SRCS} ${LIBNAME} -o ${NAME}

${NAME}: ${OBJS}

all	: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

