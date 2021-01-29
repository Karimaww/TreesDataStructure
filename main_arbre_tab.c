#include <stdlib.h>
#include <stdio.h>
#include "arbre_lexicographique_tab.h"

int main(int argc, char **argv) {

  /* a completer. Exercice 6, question 2 */

  if (argc != 2){
    printf("I expected one argument :\n");
    exit(1);
  }

  PNoeudTab a = NULL;
  //Ajout de noeud principal
  a = ajouter_mot(a, ".");
  /*
  a = ajouter_mot(a, "avion");
  a = ajouter_mot(a, "avaler");
  a = ajouter_mot(a, "arbalet");
  a = ajouter_mot(a, "bateau");
  */
  //La lecture de dico
  a = lire_dico("french_za");
  printf("Affichage de l'arbre : \n");
  afficher_dico(a);

  //Tests
  if (rechercher_mot(a, argv[1]) == 1){
    printf("Le mot %s est dans le dictionnaire\n", argv[1]);
  }
  else{
    printf("Le mot %s n'appartient pas a ce dictionnaire\n", argv[1]);
  }

  detruire_dico(a);

  return 0;
}
