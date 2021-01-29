#include "arbre_lexicographique.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

PNoeud creer_noeud(char lettre){
  PNoeud pn=(PNoeud)malloc(sizeof(Noeud));
  if (pn==NULL) {
    printf("Impossible d'allouer un noeud\n");
    return NULL;
  }

  pn->lettre=lettre;
  pn->fin_de_mot=non_fin;
  pn->frere_suivant=NULL;
  pn->fils=NULL;
  return pn;
}

PNoeud rechercher_lettre(PNoeud d, char lettre) {
  if (d == NULL) return NULL;

  if (d->lettre == lettre) return d;

  if (d->lettre>lettre) return NULL;

  return rechercher_lettre(d->frere_suivant, lettre);
}


int rechercher_mot(PNoeud dico, char *mot) {
  PNoeud p = rechercher_lettre(dico, *mot);

  if(p == NULL) return 0;

  if(strlen(mot) == 1) {
    return p->fin_de_mot == fin;
  }

  return rechercher_mot(p->fils, mot+1);
}

PNoeud ajouter_lettre(PNoeud d, PNoeud lettre) {
  if (d == NULL) return lettre;

  if (d->lettre == lettre->lettre) {
    return lettre;
  }

  if (d->lettre > lettre->lettre) {
    lettre->frere_suivant = d;
    return lettre;
  }

  d->frere_suivant = ajouter_lettre(d->frere_suivant, lettre);
  return d;
}

PNoeud ajouter_mot(PNoeud racine, char *mot) {
  if(strlen(mot) == 0) return racine;

  PNoeud fils = rechercher_lettre(racine, *mot);
  if(fils == NULL) {
    fils = creer_noeud(*mot);
  }

  if(strlen(mot) == 1) {
    fils->fin_de_mot = fin;
  }

  fils->fils = ajouter_mot(fils->fils, mot+1);
  return ajouter_lettre(racine, fils);
}

int taille(PNoeud racine) {
  if (racine==NULL) {
    return 0;
  }
  else {
    return 1+taille(racine->frere_suivant);
  }
}

void afficher_mots(PNoeud n, char mot_en_cours[], int index) {

  /* a completer. Exercice 4, question 1 */
  /* Si l'arbre est vide */
  if (n == NULL) return;

  /* On ajoute une lettre au mot*/
  mot_en_cours[index] = n->lettre;

  /* Si la lettre est la derniere dans l'arbre */
  if(n->fin_de_mot == fin){
    mot_en_cours[index+1] = '\0';
    printf("%s\n", mot_en_cours);
  }

  /*On continue a parcourir l'arbre*/
  afficher_mots(n->fils, mot_en_cours, (index+1));
  afficher_mots(n->frere_suivant, mot_en_cours, index);

}

void afficher_dico(PNoeud racine) {

  /* a completer. Exercice 4, question 1 */
  char mot_en_cours[LONGUEUR_MAX_MOT];
  afficher_mots(racine, mot_en_cours, 0);
}

void detruire_dico(PNoeud dico) {

  /* a completer. Exercice 4, question 2 */
  /* Si la lettre est la derniere */
  if (dico == NULL) return;

  /* Destruction de fils et de freres de l'arbre */
  detruire_dico(dico->fils);
  detruire_dico(dico->frere_suivant);
  free(dico);

}

PNoeud lire_dico(const char *nom_fichier) {

  /* a completer. Exercice 4, question 3 */
  /* Ouverture du fichier */
  FILE *f=fopen(nom_fichier, "r");
  PNoeud n = NULL;
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
