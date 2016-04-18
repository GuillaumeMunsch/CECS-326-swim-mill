#Makefile

NAME	= CECS-326

all:
	make -C fish_dir/
	make -C pellet_dir/
	make -C coordinator_dir/
clean:
	make clean -C fish_dir/
	make clean -C pellet_dir/
	make clean -C coordinator_dir/

fclean: clean
	make fclean -C fish_dir/
	make fclean -C pellet_dir/
	make fclean -C coordinator_dir/

re: fclean all
