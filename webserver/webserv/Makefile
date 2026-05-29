NAME = Webserv

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98
CPPFLAGS = -Iincludes

SRCS =	srcs/main.cpp \
		srcs/utils/UtilsServer.cpp srcs/utils/Getters.cpp srcs/utils/Setters.cpp \
		srcs/ParseRequest/ParseRequest.cpp \
		srcs/ParseConfigFile/ServerConfig.cpp srcs/ParseConfigFile/LocationConfig.cpp srcs/ParseConfigFile/ParseConfig.cpp\
		srcs/Router/HandleRequest.cpp \
		srcs/Response/Response.cpp srcs/Response/Method.cpp \
		srcs/Response/Errors.cpp srcs/Response/Cgi.cpp \
		srcs/Response/Get.cpp srcs/Response/Post.cpp srcs/Response/Delete.cpp \
		srcs/server-client/client.cpp srcs/server-client/server.cpp srcs/server-client/socket.cpp \

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