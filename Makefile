##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

CC	= g++

NAME	=  arcade

SRC	=	main.cpp \
		Core.cpp \
		C_encapsulation.cpp \
		Error.cpp \
		Error_find.cpp \

OBJ =	$(SRC:.cpp=.o)

CPPFLAGS += -I./include

CFLAGS += -std=c++20 -Wall -Wextra -Werror -g3

LDFLAGS += -L/path/to/sfml/lib -lncurses -lsfml-graphics -lsfml-window -ldl -lsfml-system -lSDL2 -lSDL2_ttf

all: $(NAME)

graphicals:
	$(MAKE) -C src/LibGraphic/Ncurses/
	$(MAKE) -C src/LibGraphic/Sdl/
	$(MAKE) -C src/LibGraphic/Sfml/

games:
	$(MAKE) -C src/Games/Nibbler/
	$(MAKE) -C src/Games/Snake/

core:	$(OBJ)
	$(CC) -g -o $(NAME) $(OBJ) $(LDFLAGS)

$(NAME):	graphicals		games 	$(OBJ)
	$(CC) -g -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(MAKE) clean -C src/LibGraphic/Ncurses/
	$(MAKE) clean -C src/LibGraphic/Sdl/
	$(MAKE) clean -C src/LibGraphic/Sfml/
	$(MAKE) clean -C src/Games/Nibbler/
	$(MAKE) clean -C src/Games/Snake/
	$(RM) -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C src/LibGraphic/Ncurses/
	$(MAKE) fclean -C src/LibGraphic/Sdl/
	$(MAKE) fclean -C src/LibGraphic/Sfml/
	$(MAKE) fclean -C src/Games/Nibbler/
	$(MAKE) fclean -C src/Games/Snake/
	rm -f $(NAME)

re: fclean all

.PHONY: re all clean fclean graphicals games core