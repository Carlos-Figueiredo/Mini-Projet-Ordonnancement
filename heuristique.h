#include <stdio.h>

struct Problem {
  int* weights;
  int* dates;
  int* schedule;
  int* unavailabilities;
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

int place_available(struct Problem p) {
  int times[6];
  int* w_it = p.weights;
  for (int* it=p.schedule; it!=p.schedule+p.size; ++it) {
    times[*it] += *(w_it++);
  }

  int* a_it = p.unavailabilities;
  for (int* it=times; it!=times+6; ++it) {
    if (*it > *(a_it++)) {
      return 1;
    }
  }
  return 0;
}

void heuristique1(struct Problem p) {
  int* sch_it = p.schedule;
  int i=0;
  for (int* it=p.weights; it!=p.weights+p.size; ++it) {
    *(sch_it++) = 7;
  }
}
