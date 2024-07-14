##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

CC	= g++

DIR	=	./../../../lib/

NAME	=  $(DIR)/arcade_nibbler.so

SRC	=	Nibbler.cpp \

OBJ =	$(SRC:.cpp=.o)

CPPFLAGS += -I./include -fPIC

CFLAGS += -std=c++20 -Wall -Wextra -Werror -g3

all: $(NAME)

$(NAME):	$(OBJ)
	@mkdir -p $(DIR)
	$(CC) -g -shared -o $(NAME) $(OBJ)

clean:
	$(RM) -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re all clean fclean