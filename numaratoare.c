/* Matei Bianca-Larisa -> 322CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int numere[150], s, n, indice, nr = 0, ok = 0, first;
FILE* file_out;

/* suma elementelor din vector */
int suma(int pas) {
  int i, S = 0;
  for (i = pas; i >= 1; i--)
    S += numere[i];
    return S;
}

/* verific daca varianta este valida (ma intereseaza si ca numarele sa fie
    in ordine descrescatoare) */
int valid(int pas) {
  if (suma(pas) > s || numere[pas - 1] < numere[pas])
    return 0;
  return 1;
}

/* este varianta finala daca suma este egala cu s si are n termeni */
int final(int pas) {
  if(suma(pas) != s || pas != n)
    return 0;
  return 1;
}

void tipar(int pas) {
  int i;
  fprintf(file_out, "%d=", s);
  for (i = 1; i < pas; i++)
    fprintf(file_out, "%d+", numere[i]);
  fprintf(file_out, "%d", numere[i]);
}

void back(int pas) {
  int i;
  for (i = first; i >= 1; i--) {
    numere[pas] = i;
    if (valid(pas)) {
      if (final(pas)) {
        /* daca are indicele cautat, afisez si ma opresc */
        if (nr == indice) {
          tipar(pas);
          ok = 1;
        }
        nr++;
      }
      else
        back(pas + 1);
    }
  if (ok == 1)
    break;
  }
}

int main() {
  FILE *file_in = fopen("numaratoare.in", "r");
  file_out = fopen("numaratoare.out", "w");
  fscanf(file_in, "%d%d%d", &s, &n, &indice);
  numere[0] = s;
  /* elementul de la care incep */
  first = s - n + 1;
  back(1);
  if(!ok)
    fprintf(file_out, "-");

  fclose(file_in);
  fclose(file_out);
}
