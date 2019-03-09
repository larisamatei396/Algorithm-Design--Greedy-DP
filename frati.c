/* Matei Bianca-Larisa -> 322CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  unsigned short jocuri;
  unsigned short benzi;
  int index;
} Castig;

int comparator_jon(const void *p, const void *q) {
  Castig castig1 = *(Castig*)p;
  Castig castig2 = *(Castig*)q;

  int sum1, sum2;
  sum1 = castig1.jocuri + castig1.benzi;
  sum2 = castig2.jocuri + castig2.benzi;

  /* ordonez descrescator in functie de suma dintre jocuri video si benzi
    desenate */
  if (sum1 < sum2)
    return 1;

  /* daca suma este egala, ordonez descrescator in functie de numarul de
    jocuri */
  if (sum1 == sum2 && castig1.jocuri < castig2.jocuri)
    return 1;
  return 0;
}

int comparator_sam(const void *p, const void *q) {
  Castig castig1 = *(Castig*)p;
  Castig castig2 = *(Castig*)q;

  int sum1, sum2;
  sum1 = castig1.jocuri + castig1.benzi;
  sum2 = castig2.jocuri + castig2.benzi;

  /* ordonez descrescator in functie de suma dintre jocuri video si benzi
    desenate */
  if (sum1 < sum2)
    return 1;

  /* daca suma este egala, ordonez descrescator in functie de numarul de
    benzi */
  if (sum1 == sum2 && castig1.benzi < castig2.benzi)
    return 1;
  return 0;
}

int main() {
  FILE *file_in = fopen("frati.in", "r");
  FILE *file_out;
  int N, i, j = 0, k = 0, jocuri = 0, benzi = 0;
  fscanf(file_in, "%d", &N);

  Castig* jon = malloc(N * sizeof(Castig));
  Castig* sam = malloc(N * sizeof(Castig));
  int *viz = malloc(N * sizeof(int));
  /* citesc datele din fisier */
  for (i = 0; i < N; i++) {
    fscanf(file_in, "%hu", &jon[i].jocuri);
    sam[i].jocuri = jon[i].jocuri;
    fscanf(file_in, "%hu", &jon[i].benzi);
    sam[i].benzi = jon[i].benzi;
    jon[i].index = i;
    sam[i].index = i;
  }

  /* ordonez cei doi vectori */
  qsort((void*)jon, N, sizeof(jon[0]), comparator_jon);
  qsort((void*)sam, N, sizeof(sam[0]), comparator_sam);

  i = 0;
  while (k < N) {
    /* este randul lui Jon */
    if (k % 2 == 0) {
      while (1) {
        if (viz[jon[i].index] != 1) {
          jocuri += jon[i].jocuri;
          viz[jon[i].index] = 1;
          i++;
          break;
        }
        else
          i++;
      }
    }
    /* randul lui Sam */
    if (k % 2 == 1) {
      while (1) {
        if (viz[sam[j].index] != 1) {
          benzi += sam[j].benzi;
          viz[sam[j].index] = 1;
          j++;
          break;
        }
        else
          j++;
      }
    }
    k++;
  }
  file_out = fopen("frati.out", "w");
  fprintf(file_out, "%d %d", jocuri, benzi);
  fclose(file_in);
  fclose(file_out);
  return 0;
}
