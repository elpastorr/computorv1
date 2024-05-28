NAME = computor

SRCS = computor.cpp liste.cpp utils.cpp

OBJS	= ${SRCS:.cpp=.o}

FLAGS = -Wall -Wextra -Werror -I -std=c++98

all :	${NAME}

%.o:	%.cpp
	c++ ${FLAGS} -c $< -o $@

${NAME} : ${OBJS}
	c++ $(FLAGS) ${OBJS} -o ${NAME}

clean :	${OBJS}
	rm -rf ${OBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all

.PHONY : all clean fclean re