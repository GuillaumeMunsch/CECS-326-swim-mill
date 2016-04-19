#ifndef UTILS_H_
# define UTILS_H_

# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/sem.h>

# define RIVER_HEIGHT 5
# define RIVER_WIDTH 10

# define FISH_CYCLE 500000 /* In microseconds */
# define PELLET_CYCLE 3500000 /* In microseconds */
# define COORDINATOR_CYCLE 500000 /* In microseconds */

# define GETBIT(c, bit_number) ((c >> bit_number) & 1)
# define SETBIT(c, bit_number, val) (c ^= (-val ^ c) & (1 << bit_number))

# define ISFISHBIT(field) (GETBIT(field, 1))
# define SETFISHBIT(field) (SETBIT(field, 1, 1))
# define UNSETFISHBIT(field) (SETBIT(field, 1, 0))
# define ISPELLETBIT(field) (GETBIT(field, 2))
# define SETPELLETBIT(field) (SETBIT(field, 2, 1))
# define UNSETPELLETBIT(field) (SETBIT(field, 2, 0))

# define ABS(val) ((val < 0) ? -val : val)

void my_exit(char *msg);
key_t get_key();
char *get_river(key_t k);
int get_map_lock(key_t k);
void lock_map(int map_lock);
void unlock_map(int map_lock);
void print_map(char *river, int map_lock);

#endif /* !UTILS_H_ */
