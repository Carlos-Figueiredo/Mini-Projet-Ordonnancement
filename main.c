#include "heuristique.h"
#include <stdio.h>

#define SIZE 5

int main(int argc, char** argv) {
  int weights[SIZE] = {1, 2, 3, 2, 3};
  int dates[SIZE]   = {2, 3, 4, 4, 5};
  int unavailabilities[3] = {4, 3, 5};
  int starts[6] = {0, 0, 0, 5, 5, 6};
  int schedule[SIZE] = {7,7,7,7,7};

  struct Problem p;

  p.weights = weights;
  p.dates = dates;
  p.schedule = schedule;
  p.unavailabilities = unavailabilities;
  p.starts = starts;
  p.size = SIZE;

	printf("Heuristique 1\n\n");
  // résultats attendu pour h1: {1,2,3,,}
  heuristique1(p);
  display_solution(p);

	printf("\n\nHeuristique 2\n\n");
  p.schedule = schedule;
	heuristique2(p);
	display_solution(p);

	printf("\n\nHeuristique 3\n\n");
  p.schedule = schedule;
  heuristique3(p);
  display_solution(p);

  /*int full[3] = {0,0,0};
  place_available(p, full);
  print_array(full, 3);
  printf("\n");*/

  return 0;
}
