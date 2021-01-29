#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "abr.h"

int main(int argc, char **argv)
{
  /* a completer. Exercice 3, question 1 */
  if(argc != 3){
    printf("I expected two arguments :\n");
    exit(1);
  }
  int nbIt = atoi(argv[2]);
  for(int i=0; i<nbIt; i++){
    Lm_mot *lmots = lire_dico_Lmot("french_za");
    Nd_mot *abr = Lm2abr(lmots);

    if(chercher_Nd_mot(abr, argv[1])){
      printf("Le mot %s est dans le dictionnaire\n", argv[1]);
    }
    else{
      printf("Le mot %s n'appartient pas a ce dictionnaire\n", argv[1]);
    }

    detruire_abr_mot(abr);
  }

  return 0;
}
