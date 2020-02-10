#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBEROFTASKS 5
#define NBSOLUTIONS 50
#define BOUNDARY1 25 //number of solutions kept while prunning
#define BOUNDARY2 40 //between boudaries 1 and 2 make mutations, after boundary 2 insert random solutions

struct Problem{
	int number_of_tasks;
	int* placements;
	int* indisponibleStart;
	int* indisponibleFinish;
	int* durations;
	int* limitDate;
};

//number of tasks on M7
int not_done(struct Problem * p){
  int sum;
	sum = 0;
  for (int i = 0; i < p->number_of_tasks; ++i){
    sum += *(p->placements + 6*(p->number_of_tasks) + i);
  }
	return sum;
}

//number of tasks not done in time (objective)
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

//1 if solution is valid, 0 otherwise
int is_valid(struct Problem* p){
	int sum;
  // Guarantees that we finish before the indisponibility starts
  for (int j = 0; j < 3; j++) {
    sum = 0;
    for (int i = 0; i < p->number_of_tasks; i++) {
      sum += *(p->placements + j * p->number_of_tasks + i) * *(p->durations + i);
    }
    if(sum > *(p->indisponibleStart + j)){
      //printf("Tasks in machine %d finish at %d and the indisponibility starts at %d\n", j, sum, *(p->indisponibleStart + j));
      return 0;
		}
  }
  // All tasks are in at least one machine
  for (int i = 0; i < p->number_of_tasks; i++) {
    sum = 0;
    for (int j = 0; j < 7; j++){
      sum += *(p->placements + j*p->number_of_tasks + i);
    }
    if(sum != 1) {
      //printf("Task %d is not in any machine", i);
      return 0;
		}
  }
  // From 1 to 3, all finish before deadline
  for (int j = 0; j < 3; j++) {
    sum = 0;
    for(int i = 0; i < p->number_of_tasks; i++){
      sum += *(p->placements + j*p->number_of_tasks + i) * *(p->durations + i);
      if(*(p->placements + j*p->number_of_tasks + i)  && sum > *(p->limitDate + i)) {
        //printf("Task %d in machine %d doesnt finish before its deadline\n", i, j);
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
        //printf("Task %d in machine %d doesnt finish before its deadline\n", i, j);
        return 0;
			}
		}
  }

  return 1;
}
void copy_placements(int* plac1, int* plac2){

  for (int i = 0; i < 7; i++) {
    for (int h = 0; h < NUMBEROFTASKS; h++) {
      *(plac1 + i*5 + h) = *(plac2 + i*5 + h);
    }
  }
}


//compare two solutions
int compare(const void* solutionA, const void * solutionB){
	int nb_delayedA;
	int nb_delayedB;
	nb_delayedA = not_done((struct Problem *) solutionA);
	nb_delayedB = not_done((struct Problem *) solutionB);
	return nb_delayedA - nb_delayedB;
}

// Displays placement
void display(struct Problem* p) {
	for (int j = 0; j < 7; j++) {
		for (int i = 0; i < p->number_of_tasks; i++) {
			printf("%d ", *(p->placements + j*p->number_of_tasks + i));
		}
		printf("\n");
	}
}

// Creates our mutations - We take one task of the machine it is currently one and assign it to a random machine
int* mutation(int copie_placements[7][NUMBEROFTASKS]) {
  int* new_vec = malloc(7 * NUMBEROFTASKS * sizeof(int));
  int change = rand() % NUMBEROFTASKS;
  int new_machine = rand() % 7;
  int i;

  for (int i = 0; i < 7; i++) {
    for (int h = 0; h < NUMBEROFTASKS; h++) {
      *(new_vec + 5*i + h) = copie_placements[i][h];
    }
  }

  for(i = 0; i < 7; i++) {
    if(*(new_vec + 5*i + change) == 1)
      *(new_vec + 5*i + change) = 0;
  }

  *(new_vec + 5*new_machine + change) = 1;

  return new_vec;
}

// Generates a new member of the new generation
float new_son(struct Problem* solutions[NBSOLUTIONS], int* placements_new) {
  int fit[NBSOLUTIONS];
  int sum = 0;
  float avg;

  for (int i = 0; i < NBSOLUTIONS; i++) {
    fit[i] = NUMBEROFTASKS - not_done(solutions[i]); // How many tasks were not late
    sum += fit[i];
  }

  // Get the avg fit for further analysis later
  avg = (double) sum/NBSOLUTIONS;

  // Roulette (choose which member of the old generation is going to be the father - the higher the fit, the bigger the chance)
  int luck = rand();
  luck = luck%sum;
  int select_ind;
  sum = 0;

  for (int i = 0; i < NBSOLUTIONS; i++) {
    if(sum <= luck && sum + fit[i] >= luck)
      select_ind = i;
    sum += fit[i];
  }

  int copie_placements[7][NUMBEROFTASKS];

  copy_placements(&copie_placements[0][0], solutions[select_ind]->placements);

  // Tries different mutations until we find a son that obeys all the requirements
  do{
    copy_placements(solutions[select_ind]->placements, mutation(copie_placements));
  } while(!is_valid(solutions[select_ind]));

  int aux;

  copy_placements(placements_new, solutions[select_ind]->placements);
  copy_placements(solutions[select_ind]->placements, &copie_placements[0][0]);

  return avg;
}

struct Problem* best(struct Problem* solutions[NBSOLUTIONS]) {
	int best = not_done(solutions[0]);
	struct Problem* best_it = solutions[0];
	for (int i = 0; i < NBSOLUTIONS; i++) {
		if (not_done(solutions[i]) < best) {
				best = not_done(solutions[i]);
				best_it = solutions[i];
		}
	}
	return best_it;
}
