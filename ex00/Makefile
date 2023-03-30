SRCS		= main.cpp BitcoinExchange.cpp Date.cpp

OBJS		= ${SRCS:.cpp=.opp}

HEADER		= BitcoinExchange.hpp

HEADER2		= Date.hpp

NAME		= btc

CC			= c++

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -std=c++98 -fsanitize=address

all:		${NAME}

%.opp:	%.cpp ${HEADER} ${HEADER2}
		${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re