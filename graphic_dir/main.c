#include <curses.h>
#include <ncurses.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
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
  attron(COLOR_PAIR(BLUE));
  for (i = 0; i < RIVER_HEIGHT + 2; ++i)
  {
      strncpy(line, &(map[i * (RIVER_WIDTH + 2)]), (RIVER_WIDTH + 2) * sizeof(*line));
      mvprintw(i, 0, line);
  }
  attroff(COLOR_PAIR(BLUE));
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
        attron(COLOR_PAIR(RED));
        mvprintw(i + 1, j + 1, "F");
        attroff(COLOR_PAIR(RED));
      }
      else
      {
        attron(COLOR_PAIR(GREEN));
        mvprintw(i + 1, j + 1, "o");
        attroff(COLOR_PAIR(GREEN));
      }
    }
  unlock_map(map_lock);
}

void sigquit_handler(int signal)
{
  endwin();
  fprintf(stderr, "Exiting UI\n");
  exit(1);
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
  start_color();
  init_pair(1, COLOR_CYAN, COLOR_BLUE);
  init_pair(2, COLOR_RED, COLOR_BLUE);
  init_pair(3, COLOR_GREEN, COLOR_BLUE);
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
