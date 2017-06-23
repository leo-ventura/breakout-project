#include <stdio.h>
#include <stdlib.h>

typedef struct _PLAYER {
  int points;
  char name[20];
} PLAYER;

int main(void){
  FILE *parq;
  PLAYER recordistas[5];
  int i;

  parq = fopen("rankings.bin", "r+");
  if (!parq){
    perror("Nao abriu: ");
    return 1;
  }
  else{
    fread(recordistas, sizeof(PLAYER), 5, parq);
    for (i=0;i<5;i++)  puts(recordistas[i].name);
    for (i=0;i<5;i++)  printf(" %d\n", recordistas[i].points);
  }
}
