/* Matei Bianca-Larisa -> 322CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

int main() {
  FILE *file_in = fopen("planificare.in", "r");
  FILE *file_out;
  int P, D, B, i, j, sum, dif, aux;

  /* citesc din fisier */
  fscanf(file_in, "%d %d %d", &P, &D, &B);
  int durate[P + 1], concursuri[P + 1];
  long cost[P + 1], pierderi[P + 1][P + 1];

  for (i = 1; i <= P; ++i)
    fscanf(file_in, "%d", &durate[i]);

  /* initializez matricea cu LONG_MAX (doar deasupra diagonalei principale) */
  for (i = P; i >= 1; --i) {
    aux = i + 1;
    for (j = P; j >= aux; --j)
      pierderi[i][j] = LONG_MAX;
  }

  /* creez matricea de pierderi */
  for (i = 1; i < P; ++i) {
    j = i;
    dif = D - durate[i];
    pierderi[i][j] = dif * dif * dif;
    sum = durate[i];
    while (1) {
      ++j;
      sum += B;
      sum += durate[j];
      /* daca nu mai pot grupa probe */
      if (sum > D)
        break;
      dif = D - sum;
      pierderi[i][j] = dif * dif * dif;
      if (j == P)
        pierderi[i][j] = 0;
    }
  }
  /* calculez costul minim si numarul de grupari */
  pierderi[P][P] = 0;
  cost[0] = 0;
  concursuri[0] = 0;
  for (j = 1; j <= P; ++j) {
    cost[j] = LONG_MAX;
    for (i = 1; i <= j; ++i)
      if (pierderi[i][j] != LONG_MAX
          && (cost[i - 1] + pierderi[i][j] < cost[j])) {
        cost[j] = cost[i - 1] + pierderi[i][j];
        concursuri[j] = concursuri[i - 1] + 1;
      }
  }
  file_out = fopen("planificare.out", "w");
  fprintf(file_out, "%ld %d", cost[P], concursuri[P]);

  fclose(file_in);
  fclose(file_out);
  return 0;
}
