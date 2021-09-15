SRCS =  srcs/philo.c		\
		srcs/philo_utils.c		\
		srcs/philo_utils_2.c		\
		srcs/init_thread.c		\
		srcs/init_mutex.c		\
		srcs/launch_thread.c	\
		srcs/launch_waiter.c

OBJS = ${SRCS:.c=.o}

INCLUDE =	-Iinclude

NAME = philo

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -pthread -fsanitize=thread -g

DEBUG_FLAG = -g3

.c.o:		${SRCS}
			${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${CC} ${OBJS} ${CFLAGS} ${INCLUDE} -o ${NAME}

debug:		${OBJS}
			${CC} ${OBJS} ${CFLAGS} ${DEBUG_FLAG} ${INCLUDE} -o ${NAME}

all: 		${NAME}

clean:
			rm -f srcs/*.o

fclean:		clean
			rm -f ${NAME}
			rm -rf philo.dSYM

re:			fclean all

.PHONY:		all fclean clean re debug
