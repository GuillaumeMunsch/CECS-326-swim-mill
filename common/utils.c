#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "utils.h"

void my_exit(char *msg)
{
  fprintf(stderr, "Error: %s\n", msg);
  exit(1);
}

key_t get_key()
{
  key_t k;

  if ((k = ftok(".", 0)) == -1)
    my_exit("Fail ftok");
  return (k);
}

char *get_river(key_t k)
{
  int shm_id;
  char *river;

  if ((shm_id = shmget(k, RIVER_HEIGHT * RIVER_WIDTH, SHM_R | SHM_W)) == -1)
    my_exit("Fail on getting shm");
  if ((river = shmat(shm_id, NULL, SHM_R | SHM_W)) == (void *)-1)
    my_exit("Fail on getting river");
  return (river);
}

int get_map_lock(key_t k)
{
  int map_lock;

  if ((map_lock = semget(k, 1, SHM_R | SHM_W)) == -1)
    my_exit("Fail on getting sem");
  return (map_lock);
}

void lock_map(int map_lock)
{
  struct sembuf op;

  op.sem_num = 0;
  op.sem_flg = 0;
  op.sem_op = -1;
  if (semop(map_lock, &op, 1) == -1)
    my_exit("Fail on locking map");
}

void unlock_map(int map_lock)
{
  struct sembuf op;

  op.sem_num = 0;
  op.sem_flg = 0;
  op.sem_op = 1;
  if (semop(map_lock, &op, 1) == -1)
    my_exit("Fail on unlocking map");
}

void print_map(char *river, int map_lock)
{
  int i;

  lock_map(map_lock);
  for (i = 0; i < RIVER_WIDTH * RIVER_HEIGHT; ++i)
  {
    if (!(ISFISHBIT(river[i])) && !(ISPELLETBIT(river[i])))
      write(1, ".", 1);
    else if (ISFISHBIT(river[i]) && !(ISPELLETBIT(river[i])))
      write(1, "F", 1);
    else if (ISPELLETBIT(river[i]) && !(ISFISHBIT(river[i])))
      write(1, "p", 1);
    else
      write(1, "X", 1);
    if (i % RIVER_WIDTH == RIVER_WIDTH - 1)
      write(1, "\n", 1);
  }
  unlock_map(map_lock);
  write(1, "\n", 1);
}
