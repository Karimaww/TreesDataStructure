#include <stdio.h>
#include <stdlib.h>
#include "arbre_lexicographique.h"


int main( int argc, char **argv )
{

  /* a completer. Exercice 4, question 4 */

  if (argc != 3){
    printf("I expected two arguments :\n");
    exit(1);
  }
  int nbIt = atoi(argv[2]);

  PNoeud arbre = lire_dico("french_za");
  printf("Affichage de l'arbre : \n");
  afficher_dico(arbre);

  for(int i=0; i<nbIt; i++){

    if(rechercher_mot(arbre, argv[1]) == 1){
      printf("Le mot %s est dans le dictionnaire\n", argv[1]);
    }
    else{
      printf("Le mot %s n'appartient pas a ce dictionnaire\n", argv[1]);
    }

  }

  detruire_dico(arbre);

/*
  PNoeud n = NULL;
  n = ajouter_mot(n, "arbalette");
  n = ajouter_mot(n, "arbre");
  n = ajouter_mot(n, "avion");
  n = ajouter_mot(n, "avaler");
  n = ajouter_mot(n, "aval");
  n = ajouter_mot(n, "bateau");
  printf("Affichage de l'arbre : \n");
  afficher_dico(n);
  detruire_dico(n);
  */
/*
  printf("%d %d %d %d %d\n",
         rechercher_mot(n, "avion"),
         rechercher_mot(n, "aval"),
         rechercher_mot(n, "bateau"),
         rechercher_mot(n, "avale"),
         rechercher_mot(n, "avaler"));
  detruire_dico(n);
*/
  return 0;
}
