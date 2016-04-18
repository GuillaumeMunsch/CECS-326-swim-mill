#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <strings.h>
#include <signal.h>
#include "coordinator.h"

void pellet_worker(pid_t pellet_pid[5])
{
  int i = 0;

  while (pellet_pid[i++] != 0);
  if (i == 5)
    return;
  if ((pellet_pid[i] = fork()) == -1)
    fprintf(stderr, "Fail on creating pellet\n");
  else if (!pellet_pid[i])
  {
    if (execlp("./pellet", "pellet", NULL) == -1)
      my_exit("Fail on launching pellet");
  }
  else
  {

  }
}

void game_loop(key_t k)
{
  int begin, curr_time = 0, i;
  pid_t pellet_pid[5], fish_pid;

  bzero(pellet_pid, 5 * sizeof(*pellet_pid));
  if ((fish_pid = fork()) == -1)
    my_exit("Failure on fork");
  else if (!fish_pid)
  {
    if (execlp("./fish", "fish", NULL) == -1)
      my_exit("Fail on launching fish");
  }
  else
  {
    usleep(500000);
    if ((begin = time(NULL)) == (time_t)-1)
      my_exit("Fail on time");
    while (curr_time < 30)
    {
      curr_time = time(NULL) - begin;
      usleep(COORDINATOR_CYCLE);
      pellet_worker(pellet_pid);
    }
    if (kill(fish_pid, SIGKILL) == -1)
      fprintf(stderr, "Failed to kill fish\n");
    for (i = 0; i < 5; ++i)
      if (pellet_pid[i] != 0)
        if (kill(pellet_pid[i], SIGKILL) == -1)
          fprintf(stderr, "Failed to kill pellet n°%d\n", i);
  }
}
