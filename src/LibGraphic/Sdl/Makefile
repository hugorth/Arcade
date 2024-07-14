##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

CC	= g++

DIR	=	./../../../lib/

NAME	=  $(DIR)/arcade_sdl2.so

SRC	=	Sdl.cpp \
		../../../Error_find.cpp \
		../../../Error.cpp \

OBJ =	$(SRC:.cpp=.o)

CPPFLAGS += -I./include -fPIC

CFLAGS += -std=c++20 -Wall -Wextra -Werror -fno-gnu-unique -ldl -lSDL2 -lSDL2_ttf -lSDL2_image -g3

all: $(NAME)

$(NAME):	$(OBJ)
	@mkdir -p $(DIR)
	$(CC) -g -shared -o $(NAME) $(OBJ) -ldl -lSDL2 -lSDL2_ttf -lSDL2_image

clean:
	$(RM) -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re all clean fclean