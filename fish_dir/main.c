#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fish.h"

char *find_pellet_line(char *river)
{
  char *pellet_line;
  int i = RIVER_WIDTH * (RIVER_HEIGHT), j;

  while (i >= 0)
  {
    pellet_line = &(river[i]);
    for (j = 0; j < RIVER_WIDTH; ++j)
      if (ISPELLETBIT(pellet_line[j]))
        return (pellet_line);
    i -= RIVER_WIDTH;
  }
  return (NULL);
}

int get_closest_pellet_pos(int fish_pos, char *line)
{
  int pellet_pos, pellet_diff = RIVER_WIDTH, i;

  for (i = 0; i < RIVER_WIDTH; ++i)
    if (ISPELLETBIT(line[i]))
    {
      if (fish_pos == i)
        return (i);
      else if (fish_pos < i)
      {
        pellet_pos = i;
        pellet_diff = i - fish_pos;
      }
      else
      {
        pellet_pos = i;
        pellet_diff = fish_pos - i;
      }
    }
  return (pellet_pos);
}

void move_fish(char *river, int *pos, char *fish_line)
{
  char *pellet_line;
  int closest_pellet_pos;

  if (!(pellet_line = find_pellet_line(river)))
    return;
  closest_pellet_pos = get_closest_pellet_pos(*pos, pellet_line);
  if (closest_pellet_pos == *pos)
    return;
  UNSETFISHBIT(fish_line[*pos]);
  *pos += (closest_pellet_pos > *pos ? 1 : -1);
  SETFISHBIT(fish_line[*pos]);
}

void exec_fish(int map_lock, char *river)
{
  char *fish_line = &river[(RIVER_HEIGHT -1) * RIVER_WIDTH];
  int pos;

  pos = RIVER_WIDTH / 2;
  lock_map(map_lock);
  puts("Putting fish into the river");
  SETFISHBIT(fish_line[pos]);
  unlock_map(map_lock);
  while (1)
  {
    print_map(river, map_lock);
    usleep(FISH_CYCLE);
    lock_map(map_lock);
    move_fish(river, &pos, fish_line);
    unlock_map(map_lock);
  }
}

int main()
{
  key_t k;
  int map_lock;
  char *river;

  puts("Fish creation\n");
  k = get_key();
  map_lock = get_map_lock(k);
  river = get_river(k);
  exec_fish(map_lock, river);
  return (0);
}
