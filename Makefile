# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 10:15:37 by ncasteln          #+#    #+#              #
#    Updated: 2024/07/09 14:53:34 by nnabaeei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	webserv

# @-Wconversion - prevent implicit cast when accuracy is lost.
# @-Wsign-conversion - prevent implicit change of sign.
# @-Wshadow - warns about variable declarations that shadow a variable declared in an outer scope.
CXXFLAGS	=	-std=c++98 -g -Wall -Wextra -Wshadow -Wconversion -Wsign-conversion #-Werror

VPATH		=	src src/sockets/socket src/sockets/listening-socket src/sockets/connected-socket src/test src/http-server src/exception

SRC			=	main.cpp \
				Http.cpp \
				Server.cpp \
				Location.cpp \
				Socket.cpp \
				ListeningSocket.cpp \
				ConnectedSocket.cpp \
				HttpServer.cpp \
				Exception.cpp \
				memoryTest.cpp \
				Conf.cpp \
				HttpRequest.cpp

HEADERS		=	./src/Http.hpp \
				./src/Server.hpp \
				./src/Location.hpp \
				./src/error.hpp \
				./src/sockets/socket/Socket.hpp \
				./src/sockets/listening-socket/ListeningSocket.hpp \
				./src/sockets/connected-socket/ConnectedSocket.hpp \
				./src/http-server/HttpServer.hpp \
				./src/exception/Exception.hpp \
				./src/test/test.hpp \
				./src/Conf.hpp \
				./src/HttpRequest.hpp

INCLUDE		=	-I./include/ -I./src -I./src/sockets/socket -I./src/sockets/listening-socket -I./src/sockets/connected-socket -I./src/http-server -I./src/exception -I./src/test 


OBJS_PATH	=	objs
OBJS		=	$(SRC:%.cpp=$(OBJS_PATH)/%.o)

VERBOSE		=	-DVERBOSE=0
ifeq ($(filter verbose,$(MAKECMDGOALS)),verbose)
	VERBOSE	=	-DVERBOSE=1
endif

# ----------------------------------------------------------------------- BASIC
all: $(NAME)

verbose: $(NAME)

$(NAME): $(OBJS)
	c++ $(CXXFLAGS) $(INCLUDE) $(OBJS) -o $(NAME) $(VERBOSE)

$(OBJS_PATH)/%.o: %.cpp $(HEADERS)
	mkdir -p $(OBJS_PATH)
	c++ $(CXXFLAGS) $(INCLUDE) -c $< -o $@ $(VERBOSE)

clean:
	rm -rf $(OBJS_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

# ----------------------------------------------------------------------- NGINX
nginx: nginx-img
	docker run --detach --name $@ -p 8000:8000 $<;
	@if [ $$(docker ps -a --filter "status=running" | grep nginx | wc -l) -ne 0 ]; then \
		echo "$(G)* nginx is running$(W)"; \
	else \
		echo "$(R)* nginx exited$(W)"; \
	fi

nginx-img:
	cd nginx && docker build -t $@ .

nginx-rm:
	docker stop nginx;
	docker rm nginx;
	docker rmi nginx-img;

G	=	\033[0;32m
Y	=	\033[0;33m
B	=	\033[0;34m
R	=	\033[0;31m
W	=	\033[0m
N	=	\033[1;30m

.PHONY: all clean fclean re nginx nginx-img nginx-rm verbose



# NAME     := webserv
# CXX      := g++
# CXXFLAGS := -std=c++98 -g -Wall -Wextra -Wshadow -Wconversion -Wsign-conversion
# CXXFLAGS += -fsanitize=address -Wshadow -Wno-shadow

# # Directories
# SRC_DIR := src
# INCLUDE_DIR := include
# OBJ_DIR := obj

# # Find all .cpp files in the SRC directory
# CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)

# # Find all .hpp files in the INCLUDE directory
# HEADERS := $(wildcard $(INCLUDE_DIR)/*.hpp) $(wildcard $(INCLUDE_DIR)/*.tpp)

# # Generate object file names
# OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(CPP_FILES:.cpp=.o)))

# all: $(NAME)

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
# 	@mkdir -p $(@D)
# 	@$(CXX)  -c -o $@ $< $(CXXFLAGS) -I$(INCLUDE_DIR)

# $(NAME): $(OBJ_FILES)
# 	@$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(NAME) $(LDFLAGS)
# 	@echo $(ORG)----- $(RESET)$(GREEN)$(NAME)$(RESET)$(ORG) as exe file is created!-----$(RESET)

# clean:
# 	@rm -rf $(OBJ_DIR)

# fclean: clean
# 	@rm -rf $(NAME)

# re: clean all

# .PHONY: all, clean, fclean, re

# BLUE	= "\033[38;5;4m"
# GREEN	= "\033[38;5;2m"
# ORG		= "\033[38;5;214m"
# RED		= "\033[38;5;196m"
# RESET	= "\033[0m"

# define BLUE		"\033[38;5;4m"
# define MAGENTA	"\033[38;5;5m"
# define CYAN		"\033[38;5;44m"
# define GREEN		"\033[38;5;2m"
# define ORG		"\033[38;5;214m"
# define RED		"\033[38;5;196m"
# define RESET		"\033[0m"