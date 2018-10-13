
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
/*
  parq = fopen("rankings.bin", "wb");
  if (!parq){
    perror("Nao abriu: ");
    return 1;
  }
  else{
    recordistas[0].points = 100;
    recordistas[1].points = 300;
    recordistas[2].points = 200;
    recordistas[3].points = 400;
    recordistas[4].points = 500;

    fgets(recordistas[0].name, 20, stdin);
    fgets(recordistas[1].name, 20, stdin);
    fgets(recordistas[2].name, 20, stdin);
    fgets(recordistas[3].name, 20, stdin);
    fgets(recordistas[4].name, 20, stdin);

    fwrite(recordistas, sizeof(PLAYER), 5, parq);
    fclose(parq);
  }
*/

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
