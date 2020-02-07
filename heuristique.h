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
  int ct = p.weights[task-1];
  for (int i=0; i!=task-1; ++i) {
    if (p.schedule[i] == place) {
      ct += p.weights[i];
    }
  }
  printf("ct: %d\n", ct);
  return (p.starts[task-1]+ct <= p.dates[task-1]);
}

/**
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

    int current_task = i;
    print_array(place, 3);
    printf("\n%d %d %d %d\n", i, p.weights[i-1], place[0], in_time(p, i, 0));
    if (place[0]>=p.weights[i-1] && in_time(p, i, 1)) {
      *(sch_it++) = 1;
      i++;
    }
    if (place[1]>=p.weights[i-1] && in_time(p, i, 2)) {
      *(sch_it++) = 2;
      i++;
    }
    if (place[2]>=p.weights[i-1] && in_time(p, i, 3)) {
      *(sch_it++) = 3;
      i++;
    }
    if (i==current_task) { //on a pas réussi à placer la tache i avant l'indisponibilité
      if (in_time(p, i, 4)) {
        *(sch_it) = 4;
        i++;
      } else if (in_time(p, i, 5)) {
        *(sch_it) = 5;
        i++;
      } else if (in_time(p, i, 6)) {
        *(sch_it) = 6;
        i++;
      } else {
        *(sch_it++) = 7;
        i++;
      }
    }
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
