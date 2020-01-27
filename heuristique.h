#include <stdio.h>

struct Problem {
  int* weights;
  int* dates;
  int* schedule;
  int* unavailabilities;
  int* curr_time;
  int* starts;
  int size;
};

void print_array(int* arr, int size) {
  int* it = arr;
  printf("{%d", *(it++));

  for (; it!=arr+size; ++it) {
    printf(", %d", *it);
  }

  printf("}");
}

int performance(int* schedule, int size) {
  int count=0;
  for (int* it=schedule; it!=schedule+size; ++it) {
    if (*it == 7) {
      count++;
    }
  }
  return count;
}

void place_available(struct Problem p, int* full) {
  int times[7] = {0,0,0,0,0,0,0};
  int* w_it = p.weights;
  for (int* it=p.schedule; it!=p.schedule+p.size; ++it) {
    times[*it-1] += *(w_it++);
  }

  int* t_it = times;
  int* a_it = p.unavailabilities;
  for (int* it=full; it!=full+3; ++it) {
    if (*(t_it++)>=*(a_it++)) {
      *it = 1;
    }
  }
}

int select_machine(Problem p, int curr_it) {
  int index = 7;
  int maxi = p.weights[curr_it];
  for (int i=0; i!=3; ++i) {
    int time_left = p.unavailabilities[i] - p.curr_time[i];
    if (time_left>=maxi && p.curr_time[i] + p.weights[curr_it] <= p.dates[curr_it]) {
      maxi = time_left;
      index = i+1;
    }
  }
  if (index==7) {
    int mini = p.curr_time[3];
    for (int i=3; i!=7; ++i) {
      if (p.curr_time[i]<=mini) {
        mini = p.curr_time[i];
        index = i+1;
      }
    }
    if (mini+p.weights[curr_it] > p.dates[curr_it]) {
      index = 7;
    }
  }
  return index;
}

/* 
 * Positionnement des taches par ordre croissant des di
 * TODO: vérifier que la tache peut passer
 * TODO: vérifier qu'une tache n'est pas en retard sinon la mettre en 7
 */
void heuristique1(struct Problem p) {
  int* sch_it = p.schedule;
  int i=1;
  while (i<=p.size) {
    int full[3] = {0,0,0};
    place_available(p, full);
    if (!full[0]) {
      *(sch_it++) = 1;
      i++;
    }
    if (!full[1]) {
      *(sch_it++) = 2;
      i++;
    }
    if (!full[2]) {
      *(sch_it++) = 3;
      i++;
    }
    if ((full[0] && full[1]) && full[2]) {
      *(sch_it++) = 7;
      i++;
    }
  }
}

/*
* Positionner la tache sur la machine où il reste le plus de place
*/
void heuristique3(struct Problem p) {
  int* sch_it = p.schedule;
  int i =0;
  while (i<p.size) {
    int machine_selected = select_machine(p, i);
    *(sch_it++) = machine_selected;
    i++;
  }
}


void display_solution(struct Problem p) {
  printf("Schedule: ");
  print_array(p.schedule, p.size);
  printf("\n\n\tM1: ");
  for (int i=0; i<p.size; ++i) {
    if (p.schedule[i] == 1) {
      printf("%d ", i+1);
    }
  }
  printf("|||");
  for (int i=0; i<p.size; ++i) {
    if (p.schedule[i] == 4) {
      printf("%d ", i+1);
    }
  }
  printf("\n\tM2: ");
  for (int i=0; i<p.size; ++i) {
    if (p.schedule[i] == 2) {
      printf("%d ", i+1);
    }
  }
  printf("|||");
  for (int i=0; i<p.size; ++i) {
    if (p.schedule[i] == 5) {
      printf("%d ", i+1);
    }
  }
  printf("\n\tM3: ");
  for (int i=0; i<p.size; ++i) {
    if (p.schedule[i] == 3) {
      printf("%d ", i+1);
    }
  }
  printf("|||");
  for (int i=0; i<p.size; ++i) {
    if (p.schedule[i] == 6) {
      printf("%d ", i+1);
    }
  }
  printf("\n\n");
  printf("Non ordonnancé: ");
  for (int i=0; i<p.size; ++i) {
    if (p.schedule[i] == 7) {
      printf("%d ", i+1);
    }
  }
  printf("\n");
  printf(" -> performance: %d\n", performance(p.schedule, p.size));
}
