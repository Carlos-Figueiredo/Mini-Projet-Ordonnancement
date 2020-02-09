#include "genetique_projet.h"

int main(){
  int placements[7][NUMBEROFTASKS] = {{0}};
  int limitDate[NUMBEROFTASKS] = {2, 3, 4, 4, 5};
  int indisponibleStart[6] = {0, 0, 0, 4, 3, 5};
  int indisponibleFinish[6] = {0, 0, 0, 5, 5, 6};
  int durations[NUMBEROFTASKS] = {1, 2, 3, 2, 3};
	int number_of_tasks = 5;
	
	struct Problem* solutions[NBSOLUTIONS];
	for (int i = 0; i < NBSOLUTIONS; i++) {
		struct Problem p;
		p.limitDate = &limitDate[0];
		p.indisponibleStart = &indisponibleStart[0];
		p.indisponibleFinish = &indisponibleFinish[0];
		p.durations = &durations[0];
		p.number_of_tasks = number_of_tasks;
		solutions[i] = &p;
	}

	//struct Problem retained_solution;
	//retained_solution = *(genetique_algo(solutions, 10));

	}
