#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define LOOP_COUNT_MIN 100
#define LOOP_COUNT_MAX 100000000

int main(int argc, char *argv[]) {
  printf("started\n");
  char *idStr;
  unsigned int	v;
  int	i = 0;
  int	iteration = 1;
  int	deadlineLimit, loopCount, maxloops;
  int currentTime;

  if(argc < 4 || argc > 5) {
    printf("Usage: %s <id> <deadlineLimit> <loop count> [max loops]\n", argv[0]);
    exit(-1);
  }
  /* Start with PID so result is unpredictable */
  v = getpid();

  /* ID string is first argument */
  idStr = argv[1];

  /* Deadline is the second argument */

  //deadlineLimit = atoi(argv[2]);

  // getCurrentSystemTime: made-up function. Has to be appropriately defined. As the name suggests gets the current system time

  //currentTime = getCurrentSystemTime();

  // setDeadline: made-up function. Has to be appropriately defined. As the name suggests, sets the deadline in microseconds by when this job has to complete

  //setDeadline(currentTime + deadlineLimit);

  /* loop count is third argument */
  loopCount = atoi(argv[3]);
  if((loopCount < LOOP_COUNT_MIN) || (loopCount > LOOP_COUNT_MAX)) {
    printf("%s: loop count must be between %d and %d (passed %d)\n", argv[0], LOOP_COUNT_MIN, LOOP_COUNT_MAX, loopCount);
    exit(-1);
  }
  /* max loops is fourth argument (if present) */
  if(argc == 5) {
    maxloops = atoi(argv[4]);
  }
  else {
    maxloops = 0;
  }

  /* Loop forever - use CTRL-C to exit the program */
  while(1) {
    /* This calculation is done to keep the value of v unpredictable. Since the compiler can't calculate it in advance (even from the original value of v and the loop count), it has to do the loop. */
    v = (v << 4) - v;
    if(++i == loopCount) {
      /* Exit if we've reached the maximum number of loops. If maxloops is 0 (or negative), this'll never happen... */
      if(iteration == maxloops) {
        break;
      }
      printf("%s:%06d\n", idStr, iteration);
      fflush(stdout);
      iteration += 1;
      i = 0;
    }
  }
  /* Print a value for v that's unpredictable so the compiler can't optimize the loop away. Note that this works because the compiler can't tell in advance that it's not an infinite loop. */
  printf("The final value of v is 0x%08x\n", v);
}
