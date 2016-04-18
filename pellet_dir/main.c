#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "pellet.h"

void move_pellet(int *pos, int *alive, char *river)
{
  if (ISFISHBIT(river[*pos]))
  {
    *alive = 0;
    return;
  }
  UNSETPELLETBIT(river[*pos]);
  *pos += RIVER_WIDTH;
  if (*pos >= RIVER_WIDTH * RIVER_HEIGHT || ISFISHBIT(river[*pos]))
    *alive = 0;
  else
    SETPELLETBIT(river[*pos]);
}

void exec_pellet(int map_lock, char *river)
{
  int alive = 0, pos;

  srand(time(NULL));
  while (!alive)
  {
    lock_map(map_lock);
    pos = rand() % ((RIVER_HEIGHT - 2) * RIVER_WIDTH);
    if (!ISPELLETBIT(river[pos]))
    {
      SETPELLETBIT(river[pos]);
      alive = 1;
    }
    unlock_map(map_lock);
  }
  while (alive)
  {
    usleep(PELLET_CYCLE);
    lock_map(map_lock);
    move_pellet(&pos, &alive, river);
    unlock_map(map_lock);
  }
  UNSETPELLETBIT(river[pos]);
}

int main(int ac, char **av)
{
  int map_lock;
  key_t k;
  char *river;

  puts("Pellet creation");
  k = get_key();
  map_lock = get_map_lock(k);
  river = get_river(k);
  exec_pellet(map_lock, river);
  puts("Pellet deletion");
  return (0);
}
