#include <strings.h>
#include <stdio.h>
#include "coordinator.h"

void setup_shm(key_t k, int *shm_id)
{
  char *river;

  if ((*shm_id = shmget(k, RIVER_HEIGHT * RIVER_WIDTH, SHM_R | SHM_W)) == -1)
    if ((*shm_id = shmget(k, RIVER_HEIGHT * RIVER_WIDTH, IPC_CREAT | SHM_R | SHM_W)) == -1)
      my_exit("Fail on creating shm");
  if ((river = shmat(*shm_id, NULL, SHM_R | SHM_W)) == (void *)-1)
    my_exit("Fail on getting river");
  bzero(river, RIVER_HEIGHT * RIVER_WIDTH * sizeof(*river));
}

void setup_sem(key_t k, int *sem_id)
{
  if ((*sem_id = semget(k, 1, SHM_R | SHM_W)) == -1)
    if ((*sem_id = semget(k, 1, IPC_CREAT | SHM_R | SHM_W)) == -1)
      my_exit("Fail on creating sem");
  if (semctl(*sem_id, 0, SETVAL, 1) == -1)
    my_exit("Fail to set map_lock");
}

void delete_shm_sem()
{
  key_t k;
  int shm_id, sem_id;

  k = get_key();
  if ((shm_id = shmget(k, RIVER_HEIGHT * RIVER_WIDTH, SHM_R | SHM_W)) == -1)
    fprintf(stderr, "Fail on getting shm\n");
  if ((sem_id = semget(k, 1, SHM_R | SHM_W)) == -1)
    fprintf(stderr, "Fail on getting sem\n");
  printf("Removing shm\n");
    if (shmctl(shm_id, IPC_RMID, NULL) == -1)
    fprintf(stderr, "Fail on removing shm\n");
  printf("Removing sem\n");
  if (semctl(sem_id, 0, IPC_RMID) == -1)
    fprintf(stderr, "Fail on removing sem\n");
}

int main(int ac, char **av)
{
  key_t k;
  int shm_id, sem_id;

  if (RIVER_HEIGHT < 3 || RIVER_HEIGHT > 10 || RIVER_WIDTH < 1 || RIVER_WIDTH > 10)
    my_exit("Witdh min = 1\nWitdh max = 10\nHeight min = 3\nHeight max = 10\n");
  k = get_key();
  setup_shm(k, &shm_id);
  setup_sem(k, &sem_id);
  game_loop(k);
  return (0);
}
