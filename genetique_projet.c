#include "genetique_projet.h"

int main(){
  int placements[7][NUMBEROFTASKS] = {{0}};
  int limitDate[NUMBEROFTASKS] = {2, 3, 4, 4, 5};
  int indisponibleStart[6] = {0, 0, 0, 4, 3, 5};
  int indisponibleFinish[6] = {0, 0, 0, 5, 5, 6};
  int durations[NUMBEROFTASKS] = {1, 2, 3, 2, 3};
	int number_of_tasks = 5;

	struct Problem p;
	p.placements = &placements[0][0];
	p.limitDate = &limitDate[0];
	p.indisponibleStart = &indisponibleStart[0];
	p.indisponibleFinish = &indisponibleFinish[0];
	p.durations = &durations[0];
	p.number_of_tasks = number_of_tasks;
	
	int nb_not_done = not_done(&p);
	printf("%d ", nb_not_done);
	int ok = is_valid(&p);
	printf("%d ", ok);
	make_random(&p);
	int comp = compare(&p, &p);
	printf("%d ", comp);

	struct Problem* solutions[NBSOLUTIONS];
	for (int i = 0; i < NBSOLUTIONS; i++) {
		int* tab = malloc(sizeof(*tab)*7*NUMBEROFTASKS);
		struct Problem* p = malloc(sizeof(*p));
		p->placements = tab;
		p->limitDate = &limitDate[0];
		p->indisponibleStart = &indisponibleStart[0];
		p->indisponibleFinish = &indisponibleFinish[0];
		p->durations = &durations[0];
		p->number_of_tasks = number_of_tasks;
		solutions[i] = p;
	}
	
	add_random_solutions(solutions, 0);
	add_mutations(solutions);
	//pruning(solutions);
	//struct Problem retained_solution;
	//retained_solution = *(genetique_algo(solutions, 10));

	}
