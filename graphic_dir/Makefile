#Makefile

CFLAGS += -W
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -ansi
CFLAGS += -pedantic
CFLAGS += -g

LDFLAGS += -lncurses

SRC		= main.c \
		../common/utils.c

OBJ		= $(SRC:.c=.o)

NAME	= graphic

$(NAME): $(OBJ)
	gcc -o $(NAME) $(LDFLAGS) $(OBJ)
	mv $(NAME) ..

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf ../$(NAME)

re: fclean all
