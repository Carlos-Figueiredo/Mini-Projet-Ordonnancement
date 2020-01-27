#include <stdio.h>

struct Problem {
  int* weights;
  int* dates;
  int* schedule;
  int* unavailabilities;
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
    if (*(t_it) <= *(a_it)) {
      *it = *(a_it++)-*(t_it++);
    } else {
      *it = 0;
    }
  }
}

int in_time(struct Problem p, int task, int place) {
  int ct = 0;
  for (int i=0; i!=p.size; ++i) {
    if (p.schedule[i] == place) {
      ct += p.weights[i];
    }
  }
  return (p.starts[task]+ct <= p.dates[task]);
}

/* 
 * Positionnement des taches par ordre croissant des di
 * TODO: vérifier que la tache peut passer
 * TODO: vérifier que la tache ne finit pas en retard
 * TODO: tester les emplacement 4, 5, 6 et y mettre les taches si elles ne sont pas en retard
 * TODO: vérifier qu'une tache n'est pas en retard sinon la mettre en 7
 */
void heuristique1(struct Problem p) {
  int* sch_it = p.schedule;
  int i=1;
  while (i<=p.size) {
    int place[3] = {0,0,0};
    place_available(p, place);

    print_array(place, 3);
    if (place[0]>=p.weights[i-1] && in_time(p, i-1, 0)) {
      *(sch_it++) = 1;
      i++;
    }
    if (place[1]>=p.weights[i-1] && in_time(p, i-1, 1)) {
      *(sch_it++) = 2;
      i++;
    }
    if (place[2]>=p.weights[i-1] && in_time(p, i-1, 2)) {
      *(sch_it++) = 3;
      i++;
    }
    if ((place[0] && place[1]) && place[2]) {
      *(sch_it++) = 7;
      i++;
    }
  }
}

void heuristique2(struct Problem p) {
  int i=1;
  int* sch_it = p.schedule;
  int* wi = p.weights;
  while (i <= p.size) {
    //temps max sur chaque machine
    int times[7] = {0,0,0,0,0,0,0};
    t_max(p, times);

    //temps max sur chaque machine après insertion de la tâche
    int times_new[7] = times;
    for (int i=1; i<=7; i++) {
      times_new[i] += *wi;
    }

    //itérer sur les machines pour trouver les candidates et celle choisie
    int* di = p.unavailabilities;
    int tmax = times_new[1];
    for (int i=1; i<=3; i++) {
      if (times_new[i] <= di) {
        if () {

        }
      }
      di++;
    }
    for (int i=4; i<=6; i++) {
      
    }


    wi++;
  }
}

void t_max(struct Problem p, int* times) {
  int* w_it = p.weights;
  for (int* it=p.schedule; it!=p.schedule+p.size; ++it) {
    times[*it-1] += *(w_it++);
  }
  //for (int* it=p.starts)
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
