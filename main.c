#include "heuristique.h"
#include <stdio.h>

#define SIZE 5

int main(int argc, char** argv) {
  int weights[SIZE] = {1, 2, 3, 4, 5};
  int dates[SIZE] = {1, 3, 2, 1, 3};
  int schedule[SIZE];
  int unavailabilities[3] = {2, 3, 2};

  struct Problem p;
  p.weights = weights;
  p.dates = dates;
  p.schedule = schedule;
  p.unavailabilities = unavailabilities;
  p.size = SIZE;

  heuristique1(p);

  printf("Schedule:\n   ");
  print_array(schedule, SIZE);

  printf("%d", place_available(p));

  printf(" -> performance: %d", performance(schedule, SIZE));
  printf("\n");
  return 0;
}
