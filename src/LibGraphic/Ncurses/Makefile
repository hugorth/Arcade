##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

CC	= g++

DIR	=	./../../../lib/

NAME	=  $(DIR)/arcade_ncurses.so

SRC	=	Ncurses.cpp \
		../../../Error_find.cpp \
		../../../Error.cpp \

OBJ =	$(SRC:.cpp=.o)

CPPFLAGS += -I./include -fPIC

CFLAGS += -std=c++20 -Wall -Wextra -Werror -lncurses -g3

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