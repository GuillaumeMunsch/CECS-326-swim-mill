#ifndef SWIM_MILL_H_
# define SWIM_MILL_H_

# include "../common/utils.h"

# define GAME_TIME 30

void game_loop(key_t k, char *river, int map_lock, int ui);
void delete_shm_sem();

#endif /* !SWIM_MILL_H_ */
