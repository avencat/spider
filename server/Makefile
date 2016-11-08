##
## Makefile for Spider server in /home/touzet_t/epitech/cpp/cpp_spider/server
## 
## Made by Theo TOUZET
## Login   <touzet_t@epitech.net>
## 
## Started on  Mon Nov  7 05:48:47 2016 Theo TOUZET
## Last update Mon Nov  7 16:05:53 2016 Theo TOUZET
##

NAME =	server

COMSRCSPATH =	../common/src

COMINCSPATH =	../common/inc

COMMONSRCS =	$(COMSRCSPATH)/SQLite3.cpp \
		$(COMSRCSPATH)/ANetwork.cpp

SRVSRCSPATH =	src

SRVINCPATH =	./inc/

SRCS =	$(COMMONSRCS) \
	$(SRVSRCSPATH)/Core.cpp \
	$(SRVSRCSPATH)/Configuration.cpp \
	$(SRVSRCSPATH)/ServerNetwork.cpp \
	$(SRVSRCSPATH)/Client.cpp \
	$(SRVSRCSPATH)/server.cpp

OBJS= $(SRCS:.cpp=.o)

LIBPATH= ../libs/

INCPATH= -I$(LIBPATH) -I$(COMINCSPATH) -I$(SRVINCPATH)

CXX= g++

CXXFLAGS= -std=c++11 -W -Wall -Wextra -Werror $(INCPATH)

LDFLAGS= -L$(LIBPATH) -lsqlite3 -lboost_thread -ldl -lboost_system-mt -lboost_regex -lboost_serialization -lboost_date_time

$(NAME): $(OBJS)
	$(CXX) -o $(NAME) $(OBJS) $(LDFLAGS)

all: $(NAME)

clean:
	rm -vf $(OBJS)

fclean:	clean
	rm -vf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
