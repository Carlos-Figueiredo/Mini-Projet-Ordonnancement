#include "genetique_projet.h"

int main(){
  int placements[7][NUMBEROFTASKS] = {{0}};
  int limitDate[NUMBEROFTASKS] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int indisponibleStart[6];
  int indisponibleFinish[6];
  int durations[NUMBEROFTASKS];
	int number_of_tasks = 10;
	//struct Problem p(placements, indisponibleStart, indisponibleFinish, durations, limitDate);
	struct Problem p;
	//p = (struct Problem) {(int*)placements, (int*)indisponibleStart, (int*)indisponibleFinish, (int*)durations, (int*) limitDate};
	p.placements = &placements[0][0];
	p.limitDate = &limitDate[0];
	p.indisponibleStart = &indisponibleStart[0];
	p.indisponibleFinish = &indisponibleFinish[0];
	p.durations = &durations[0];
	p.number_of_tasks = number_of_tasks;
	int nb_tasks;
	nb_tasks = not_done(&p);
	printf("%d ", nb_tasks);
	int ok;
	ok = compare(&p, &p);
	printf("%d ", ok);
  // Stablish indisponibilities


}
