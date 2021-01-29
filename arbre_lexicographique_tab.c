#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "arbre_lexicographique_tab.h"

PNoeudTab creer_noeud(char lettre) {
  /* a completer. Exercice 6, question 1 */
  PNoeudTab n = (PNoeudTab)malloc(sizeof(NoeudTab));

  if (n==NULL) {
    printf("Impossible d'allouer un noeud\n");
    return NULL;
  }

  n->lettre = lettre;
  n->fin_de_mot = non_fin;

  /* (PNoeudTab)calloc(26*sizeof(NoeudTab)) */
  for(int i=0; i<26; i++) n->fils[i] = NULL;

  return n;
}

int rechercher_mot(PNoeudTab dico, char *mot) {
  /* a completer. Exercice 6, question 1 */
  //Cas de base
  if(dico == NULL) return 0;

  //Si la lettre du mot est la derniere
  if(strlen(mot) == 1) return dico->fin_de_mot == fin;

  //Si le noeud est de la meme lettre
  if(dico->lettre == *mot) rechercher_mot(dico->fils[*mot - 97], mot+1);

  //On continue a chercher
  return rechercher_mot(dico->fils[*mot - 97], mot + 1);

}

PNoeudTab ajouter_mot(PNoeudTab racine, char *mot) {
  /* a completer. Exercice 6, question 1 */

  // S'il n'existe pas de lettre qu'on cherche
  if(racine == NULL) racine = creer_noeud(*mot);

  //Si on a parcouru tout le mot
  if (strlen(mot) == 0) return racine;

  //Si c'est la derniere lettre du mot
  if(strlen(mot) == 1) racine->fin_de_mot = fin;

  //Si la lettre n'est pas dans un des fils du noeud
  if(racine->fils[*mot - 97] == NULL) racine->fils[*mot - 97] = creer_noeud(*mot);
  
  //Ajout des lettres suivantes du mot
  racine->fils[*mot - 97] = ajouter_mot(racine->fils[*mot - 97], mot+1);
  return racine;
}

void afficher_mots(PNoeudTab n, char mot_en_cours[LONGUEUR_MAX_MOT], int index) {
  /* a completer. Exercice 6, question 1 */

  //Cas de base
  if (n == NULL) return;

  //On ajoute la lettre au mot_en_cours
  mot_en_cours[index] = n->lettre;

  //Si la lettre est derniere
  if(n->fin_de_mot == fin){
    mot_en_cours[index+1] = '\0';
    printf("%s\n", mot_en_cours);
  }

  for(int i=0; i<26; i++){
    afficher_mots(n->fils[i], mot_en_cours, index+1);
  }

}

void afficher_dico(PNoeudTab racine) {
  /* a completer. Exercice 6, question 1 */
  char mot_en_cours[LONGUEUR_MAX_MOT];
  for(int i=0; i<26; i++)
    afficher_mots(racine->fils[i], mot_en_cours, 0);
}

void detruire_dico(PNoeudTab dico) {
  /* a completer. Exercice 6, question 1 */
  //Cas de base
  if(dico == NULL) return;

  //Destruction de fils
  for(int i=0; i<26; i++){
    detruire_dico(dico->fils[i]);
  }
  //Destruction du noeud
  free(dico);
}

PNoeudTab lire_dico(const char *nom_fichier) {
  /* a completer. Exercice 6, question 2 */
  /* Ouverture du fichier */
  FILE *f=fopen(nom_fichier, "r");
  PNoeudTab n = NULL;
  if (f == NULL){
    printf("Erreur lors de l'ouverture du fichier %s\n",nom_fichier);
    return NULL;
  }
  char mot[100];
  /* On ajoute les mots du fichier dans l'arbre*/
  while(fscanf(f, "%s", mot) == 1){
    n = ajouter_mot(n, mot);
    /*printf("%s\n", mot);*/
  }
  /* Fermeture du fichier*/
  fclose(f);
  return n;
}
