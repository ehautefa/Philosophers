SRCS =  srcs/philo_one.c	\
		srcs/philo_utils.c	\
		srcs/init_thread.c	\
		srcs/init_mutex.c

INCLUDE =	-Iinclude

NAME = philo_one

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

DEBUG_FLAG = -g -fsanitize=thread

${NAME}:
			${CC} ${SRCS} ${CFLAGS} -o ${NAME}

debug:
			${CC} ${SRCS} ${CFLAGS} ${DEBUG_FLAG} -o ${NAME}

all: 		${NAME}

clean:
			rm -f srcs/*.o

fclean:	
			rm -f ${NAME}

re:			fclean all

.PHONY:		all fclean clean re debug
