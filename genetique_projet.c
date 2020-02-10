#include "genetique_projet.h"

int main(){
	srand(time(0));
  int placements[7][NUMBEROFTASKS] = {{0, 0, 0, 0, 0}, {0, 1, 0, 0, 0}, {0, 0, 1, 0, 0},
                                    {0, 0, 0, 0, 0}, {0, 0, 0, 1, 0}, {0, 0, 0, 0, 0}, {1, 0, 0, 0, 1}};
  /*int limitDate[NUMBEROFTASKS] = {2, 3, 4, 7, 8};
  int indisponibleStart[6] = {4, 3, 5, 0, 0, 0};
  int indisponibleFinish[6] = {0, 0, 0, 5, 5, 6};
  int durations[NUMBEROFTASKS] = {1, 2, 1, 1, 2};
	int number_of_tasks = 5;*/
	int limitDate[NUMBEROFTASKS] = {2, 3, 4, 4, 5};
  int indisponibleStart[6] = {4, 3, 5, 0, 0, 0};
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


	struct Problem* old_solutions[NBSOLUTIONS];
	for (int i = 0; i < NBSOLUTIONS; i++) {
		struct Problem* new_p = malloc(sizeof(*new_p));
    new_p->placements = malloc(7 * NUMBEROFTASKS * sizeof(int));
		copy_placements(new_p->placements, p.placements);
		new_p->limitDate = &limitDate[0];
		new_p->indisponibleStart = &indisponibleStart[0];
		new_p->indisponibleFinish = &indisponibleFinish[0];
		new_p->durations = &durations[0];
		new_p->number_of_tasks = number_of_tasks;
		old_solutions[i] = new_p;
	}

  is_valid(old_solutions[2]);

  struct Problem* new_solutions[NBSOLUTIONS];
	for (int i = 0; i < NBSOLUTIONS; i++) {
		struct Problem* new_p = malloc(sizeof(*new_p));
    new_p->placements = malloc(7 * NUMBEROFTASKS * sizeof(int));
		copy_placements(new_p->placements, p.placements);
		new_p->limitDate = &limitDate[0];
		new_p->indisponibleStart = &indisponibleStart[0];
		new_p->indisponibleFinish = &indisponibleFinish[0];
		new_p->durations = &durations[0];
		new_p->number_of_tasks = number_of_tasks;
		new_solutions[i] = new_p;
	}

  float avg[10000];

  for (int i = 0; i < 10000; i++) {
    // Generate new generation
    for (int j = 0; j < NBSOLUTIONS; j++) {
      // Generate new son
      avg[i] = new_son(old_solutions, new_solutions[j]->placements);
    }
    //copy new solutions to old solutions so we can start another generation
    for (int k = 0; k < NBSOLUTIONS; k++) {
      // We assume that all new borns respect all the rules, but just to make sure...
      if(!is_valid(new_solutions[k]))
        printf("Something is terribly wrong\n");
      copy_placements(old_solutions[k]->placements, new_solutions[k]->placements);
    }
  }

  float sum = 0;

  // We analyse how the fit evolved during the evolutionary process
  printf("%f\n", avg[0]);

  for (int i = 0; i < 10000; i++) {
    sum += avg[i];
    if(i != 0 && i % 1000 == 0){
      printf("%f\n", sum/10000);
      sum = 0;
    }
  }

	display(new_solutions[0]);

  /*

	add_random_solutions(old_solutions, 0);
	add_mutations(solutions);
	pruning(solutions);
	struct Problem retained_solution;
	retained_solution = *(genetique_algo(solutions, 10000));*/

	}
