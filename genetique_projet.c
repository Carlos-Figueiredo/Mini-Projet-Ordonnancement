#include <stdio.h>

#define NUMBEROFTASKS 10

int finalDelay(int placements[][NUMBEROFTASKS]){
  int sum = 0;

  for (int i = 0; i < NUMBEROFTASKS; i++){
    sum += placements[7][i];
  }
}

int constraints(int placements[][NUMBEROFTASKS], int indisponibleStart[], int indisponibleFinish[], int durations[], int limitDate[]){
  int sum;

  // Guarantees that we finish before the indisponibilitie starts
  for (int j = 0; j < 3; j++) {
    sum = 0;
    for (int i = 0; i < NUMBEROFTASKS; i++) {
      sum += placements[j][i] * durations[i];
    }
    if(sum > indisponibleStart[j])
      return 0;
  }

  // All tasks are in at least one machine
  for (int i = 0; i < NUMBEROFTASKS; i++) {
    sum = 0;
    for (int j = 0; j < 7; j++){
      sum += placements[j][i];
    }
    if(sum =! 1)
      return 0;
  }

  // From 1 to 3, all finish before deadline
  for (int j = 0; j < 3; j++) {
    sum = 0;
    for(int i = 0; i < NUMBEROFTASKS; i++){
      sum += placements[j][i] * durations[i];
      if(placements[j][i] && sum > limitDate[i])
        return 0;
    }
  }

  // From 4 to 6, all finish before deadline
  for (int j = 3; j < 6; j++) {
    sum = indisponibleFinish[j];
    for(int i = 0; i < NUMBEROFTASKS; i++)
      sum += placements[j][i] * durations[i];
      if(placements[j][i] && sum > limitDate[i])
        return 0;
  }

  return 1;
}

int main(){
  int placements[7][NUMBEROFTASKS];
  int limitDate[NUMBEROFTASKS] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int indisponibleStart[6];
  int indisponibleFinish[6];
  int durations[NUMBEROFTASKS];

  // Stablish indisponibilities



}
