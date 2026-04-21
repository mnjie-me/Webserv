NAME = Webserv

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98
CPPFLAGS = -Iincludes

SRCS =	srcs/main.cpp \
		srcs/utils/UtilsServer.cpp srcs/utils/Getters.cpp srcs/utils/Setters.cpp \
		srcs/ParseRequest/Request.cpp srcs/ParseRequest/ParseRequest.cpp \
		srcs/ParseConfigFile/ServerConfig.cpp srcs/ParseConfigFile/LocationConfig.cpp srcs/ParseConfigFile/ParseConfig.cpp\
		srcs/Router/Router.cpp srcs/Router/HandleRequest.cpp \
		srcs/Response/Response.cpp srcs/Response/Method.cpp srcs/Response/ExecuteMethod.cpp \
		srcs/Response/Errors.cpp srcs/Response/Cgi.cpp \

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re