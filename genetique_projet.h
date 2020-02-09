#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBEROFTASKS 10
#define NBSOLUTIONS 50
#define BOUNDARY1 25 //number of solutions kept while prunning
#define BOUNDARY2 40

//srand((unsigned) time(NULL));

int constraints(int placements[][NUMBEROFTASKS], int indisponibleStart[], int indisponibleFinish[], int durations[], int limitDate[]){
  int sum;

  // Guarantees that we finish before the indisponibilitie starts
  for (int j = 0; j < 3; j++) {
    sum = 0;
    for (int i = 0; i < NUMBEROFTASKS; i++) {
      sum += placements[j][i] * durations[i];
    }
    if(sum > indisponibleStart[j]){
      return 0;
		}
  }

  // All tasks are in at least one machine
  for (int i = 0; i < NUMBEROFTASKS; i++) {
    sum = 0;
    for (int j = 0; j < 7; j++){
      sum += placements[j][i];
    }
    if(sum =! 1) {
      return 0;
		}
  }

  // From 1 to 3, all finish before deadline
  for (int j = 0; j < 3; j++) {
    sum = 0;
    for(int i = 0; i < NUMBEROFTASKS; i++){
      sum += placements[j][i] * durations[i];
      if(placements[j][i] && sum > limitDate[i]) {
        return 0;
			}
    }
  }

  // From 4 to 6, all finish before deadline
  for (int j = 3; j < 6; j++) {
    sum = indisponibleFinish[j];
    for(int i = 0; i < NUMBEROFTASKS; i++) {
      sum += placements[j][i] * durations[i];
      if(placements[j][i] && sum > limitDate[i]) {
        return 0;
			}
		}
  }

  return 1;
}

/*---------------------------------------------------*/

struct Problem{
	int number_of_tasks;
	int* placements;
	int* indisponibleStart;
	int* indisponibleFinish;
	int* durations;
	int* limitDate;
};

int not_done(struct Problem * p){
  int sum;
	sum = 0;
  for (int i = 0; i < p->number_of_tasks; ++i){
    sum += *(p->placements + 6*(p->number_of_tasks) + i);
  }
	return sum;
}

int not_in_time(struct Problem *p){
	int nb_tasks;
	nb_tasks = 0;
	int sum;
	// From 1 to 3
  for (int j = 0; j < 3; j++) {
    sum = 0;
    for(int i = 0; i < p->number_of_tasks; i++){
      sum += (*(p->placements + j*p->number_of_tasks + i)) * (*(p->durations + i));
      if((*(p->placements + j*p->number_of_tasks + i)) && sum > (*(p->limitDate + i))){
        nb_tasks++;
			}
    }
  }
  // From 4 to 6
  for (int j = 3; j < 6; j++) {
    sum = (*(p->indisponibleFinish + j));
    for(int i = 0; i < p->number_of_tasks; i++) {
      sum += (*(p->placements + j*p->number_of_tasks + i)) * (*(p->durations + i));
      if((*(p->placements + j*p->number_of_tasks + i)) && sum > (*(p->limitDate + i))) {
        nb_tasks++;
			}
		}
	}
	// M7
	nb_tasks += not_done(p);
	return nb_tasks;
}

int is_valid(struct Problem* p){
	int sum;

  // Guarantees that we finish before the indisponibilitie starts
  for (int j = 0; j < 3; j++) {
    sum = 0;
    for (int i = 0; i < p->number_of_tasks; i++) {
      sum += *(p->placements + j*p->number_of_tasks + i) * *(p->durations +i);
    }
    if(sum > *(p->indisponibleStart + j)){
      return 0;
		}
  }

  // All tasks are in at least one machine
  for (int i = 0; i < p->number_of_tasks; i++) {
    sum = 0;
    for (int j = 0; j < 7; j++){
      sum += *(p->placements + j*p->number_of_tasks + i); 
    }
    if(sum =! 1) {
      return 0;
		}
  }

  // From 1 to 3, all finish before deadline
  for (int j = 0; j < 3; j++) {
    sum = 0;
    for(int i = 0; i < p->number_of_tasks; i++){
      sum += *(p->placements + j*p->number_of_tasks + i) * *(p->durations + i);
      if(*(p->placements + j*p->number_of_tasks + i)  && sum > *(p->limitDate + i)) {
        return 0;
			}
    }
  }

  // From 4 to 6, all finish before deadline
  for (int j = 3; j < 6; j++) {
    sum = *(p->indisponibleFinish + j);
    for(int i = 0; i < p->number_of_tasks; i++) {
      sum += *(p->placements + j*p->number_of_tasks + i) * *(p->durations +i);
      if(*(p->placements + j*p->number_of_tasks + i)  && sum > *(p->limitDate + i)) {
        return 0;
			}
		}
  }

  return 1;
}

int compare(const void* solutionA, const void * solutionB){
	int nb_delayedA;
	int nb_delayedB;
	nb_delayedA = not_in_time((struct Problem *) solutionA);
	nb_delayedB = not_in_time((struct Problem *) solutionB);
	return nb_delayedA - nb_delayedB;
}

void pruning(struct Problem* solutions[NBSOLUTIONS]) {
	qsort(solutions, NBSOLUTIONS, sizeof(*solutions[0]), compare);
}

void add_mutations(struct Problem* solutions[NBSOLUTIONS]){
	int dimension = 7 * (solutions[0]->number_of_tasks);
	//do a mutation
	for (int i = BOUNDARY1; i < BOUNDARY2; i++){
		//randomly choose one of the problem kept while prunning and a mutation location
		int model_id = rand() % BOUNDARY1;
		int mutation_id = rand() % dimension;
		//copy placements from the model to the mutant
		for (int j = 0; j < dimension; j++) {
			*(solutions[i]->placements + j) = *(solutions[model_id]->placements + j);
		}
		//add the mutation
		*(solutions[i]->placements + mutation_id) = (*(solutions[model_id]->placements + mutation_id) + 1) % 2;
	}
}

void make_random(struct Problem* p) {
	int dimension = 7 * (p->number_of_tasks);
	int value;
	for (int i = 0; i < dimension; i++) {
		value = rand() % 2;
		*(p->placements + i) = value;
	}
}

void add_random_solutions(struct Problem* solutions[NBSOLUTIONS]) {
	for (int i = BOUNDARY1; i < BOUNDARY2; i++) {
		make_random(solutions[i]);
	}
}
