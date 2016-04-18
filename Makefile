#Makefile

NAME	= CECS-326

SWIM_MILL_DIR = swim_mill_dir/
FISH_DIR = fish_dir/
PELLET_DIR = pellet_dir/

all: $(NAME)

$(NAME):
	make -C $(FISH_DIR)
	make -C $(PELLET_DIR)
	make -C $(SWIM_MILL_DIR)
clean:
	make clean -C $(FISH_DIR)
	make clean -C $(PELLET_DIR)
	make clean -C $(SWIM_MILL_DIR)

fclean: clean
	make fclean -C $(FISH_DIR)
	make fclean -C $(PELLET_DIR)
	make fclean -C $(SWIM_MILL_DIR)

re: fclean all
