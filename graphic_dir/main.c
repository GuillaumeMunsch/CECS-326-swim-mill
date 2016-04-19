#include <ncurses.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "graphic.h"

void print_arround()
{
  int i, j;
  char map[(RIVER_WIDTH + 2) * (RIVER_HEIGHT + 2)], line[RIVER_WIDTH + 3];

  printf("Size: %d\n", (RIVER_WIDTH + 2) * (RIVER_HEIGHT + 2));
  line[RIVER_WIDTH + 2] = 0;
  for (i = 0; i < (RIVER_WIDTH + 2) * (RIVER_HEIGHT + 2); ++i)
    map[i] = ' ';
  for (i = 0; i < RIVER_HEIGHT + 2; ++i)
  {
    if (i == 0 || i == (RIVER_HEIGHT + 1))
    {
      for (j = 0; j < RIVER_WIDTH + 2; ++j)
        map[(i * (RIVER_WIDTH + 2)) + j] = '#';
    }
    else
    {
      map[i * (RIVER_WIDTH + 2)] = '#';
      map[i * (RIVER_WIDTH + 2) + RIVER_WIDTH + 1] = '#';
    }
  }
  for (i = 0; i < RIVER_HEIGHT + 2; ++i)
  {
      strncpy(line, &(map[i * (RIVER_WIDTH + 2)]), (RIVER_WIDTH + 2) * sizeof(*line));
      mvprintw(i, 0, line);
  }
}

void print_body(int map_lock, char *river)
{
  int i, j;

  lock_map(map_lock);
  for (i = 0; i < RIVER_HEIGHT; ++i)
    for (j = 0; j < RIVER_WIDTH; ++j)
    {
      if (!ISFISHBIT(river[i * RIVER_WIDTH + j]) && !ISPELLETBIT(river[i * RIVER_WIDTH + j]))
        continue ;
      else if (ISFISHBIT(river[i * RIVER_WIDTH + j]))
      {
        mvprintw(i + 1, j + 1, "F");
      }
      else
      {
        mvprintw(i + 1, j + 1, "*");
      }
    }
  unlock_map(map_lock);
}

void sigquit_handler(int signal)
{
  endwin();
  my_exit("Exiting UI");
}

int main(int ac, char **av)
{
  key_t k;
  int map_lock;
  char *river;

  k = get_key();
  map_lock = get_map_lock(k);
  river = get_river(k);
  initscr();
  signal(SIGQUIT, sigquit_handler);
  signal(SIGQUIT, sigquit_handler);
  noecho();
  curs_set(FALSE);
  while (1)
  {
    clear();
    print_arround();
    print_body(map_lock, river);
    refresh();
    usleep(REFRESH_DELAY);
  }
  endwin();
  return (0);
}
