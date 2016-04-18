#Makefile

CFLAGS += -W
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -ansi
CFLAGS += -pedantic

NAME		= coordinator

SRC		= main.c \
		../common/utils.c \
		game_loop.c

OBJ		= $(SRC:.c=.o)

NAME	= coordinator

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)
	mv $(NAME) ..

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf ../$(NAME)

re: fclean all
