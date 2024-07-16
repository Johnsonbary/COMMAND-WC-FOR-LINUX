#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *ouverture(char argv[100]);
void option(int argc, char *argv[]);
void detruire(FILE *fichier);
void option_help();
void option_version();
void option_bytes(char argv[100]);
void option_chars(char argv[100]);
void option_L(char argv[100]);
void option_word(char argv[100]);
void option_sans(char *argv[], int nombre);
void option_l(char argv[100]);