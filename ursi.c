/* Matei Bianca-Larisa -> 322CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
  FILE *file_in = fopen("ursi.in", "r");
  FILE *file_out = fopen("ursi.out", "w");
  int i = 0, j, ok = 1, nr_caciulite = 0, rezultat;
  char* mesaj = malloc(2000 * sizeof(char));
  char ch;
  long mod;

  /* citesc din fisier caracter cu caracter */
  fread(&ch, sizeof(char), 1, file_in);
  mesaj[i++] = ch;
  /* daca sirul incepe cu underscore */
  if (ch == '_')
    ok = 0;
  if (ch == '^')
    nr_caciulite++;
  while (fread(&ch, sizeof(char), 1, file_in)) {
    mesaj[i++] = ch;
    if (ch == '^')
      nr_caciulite++;
  }
  /* daca sirul are numar impar de '^' */
  if (nr_caciulite % 2 == 1)
    ok = 0;

  if (ok == 0)
    rezultat = 0;
  else {
    int linii = i, coloane = nr_caciulite / 2 + 1;
    unsigned long** zambete = malloc(linii * sizeof(unsigned long*));
    for (i = 0; i < linii; i++)
      zambete[i] = malloc (coloane * sizeof(unsigned long));

    for (i = 0; i < coloane; i++)
      zambete[0][i] = 0;
    zambete[0][1] = 1;
    mod = pow(10, 9) + 7;

    for (i = 1; i < linii; i++) {
       for (j = 0; j < coloane; j++)
         if (mesaj[i] == '^') {
           if (j < coloane - 1 && j > 0)
             zambete[i][j] = ((j + 1) * zambete[i - 1][j + 1] % mod +
                             zambete[i - 1][j - 1] % mod) % mod;
           else if (j == coloane - 1)
             zambete[i][j] = zambete[i - 1][j - 1] % mod;
           else
             zambete[i][j] = (j + 1) * zambete[i - 1][j + 1] % mod;
         }
         /* daca suntem pe linia corespunzatoare unui underscore */
         else {
             zambete[i][j] = j * zambete[i - 1][j] % mod;
         }
         /* am ajuns la rezultat */
         if (i == linii - 1 && j == 0)
          break;
    }
    rezultat = zambete[linii - 1][0];
  }
  fprintf(file_out, "%d", rezultat);
  fclose(file_in);
  fclose(file_out);
  return 0;
}
