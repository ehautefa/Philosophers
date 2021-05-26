SRCS =  srcs/philo_one.c \
		srcs/philo_utils.c 

INCLUDE =	-Iinclude

NAME = philo_one

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

${NAME}:
			${CC} ${SRCS} ${CFLAGS} -o ${NAME}

all: 		${NAME}

clean:
			rm -f srcs/*.o

fclean:	
			rm -f ${NAME}

re:			fclean all

.PHONY:		all fclean clean re
