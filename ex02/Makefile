SRCS		= main.cpp PmergeMe.cpp VecMerge.cpp ListMerge.cpp

OBJS		= ${SRCS:.cpp=.opp}

HEADER		= PmergeMe.hpp

TEMPL		= PmergeMe.tpp

NAME		= PmergeMe

CC			= c++

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -std=c++98 -fsanitize=address

all:		${NAME}

%.opp:	%.cpp ${HEADER} ${TEMPL}
		${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re