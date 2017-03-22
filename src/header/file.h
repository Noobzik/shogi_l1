#ifndef PILE_H
#define PILE_H
/* Definitions des structures */

/** Structure Coordinate
 * x représente l'axe vertical
 * y représente l'axe horizontal
 */
typedef struct coordinate_s {
  int x;
  int y;
} coordinate_t;

/** Structure movement_t
 * Contient :
 * Le numéro du coups
 * Les coordonnées de départ
 * Les coordonées d'arrivee
 */
typedef struct movement_s {
  int valeur;
  coordinate_t input;
  coordinate_t output;
} movement_t;

/** file_coups_t
 * L'element de la file Contient
 * 1) Coordonée de départ et d'arrivé (Dans movement_t)
 * 2) Booleen pour la promotion ou pas
 * 3) Booleen pour la capture ou pas
 * 4) et 5) Element suivant / precedent de la liste
 */
typedef struct file_element_s {
  movement_t movement;
  int promotion;
  int capture;
  struct file_element_s *suivant;
  struct file_element_s *precedent;
} file_element_t;

/** file list
 *  Liste doublement chainé
 *  Un pointeur vers le premier element de la liste
 *  Un pointeur vers le dernier element de la liste
 *  Sa taille
 */
typedef struct file_list_s {
  file_element_t *debut;
  file_element_t *fin;
  int taille;
} file_list_t;

//======================================================================
// Prototype
//======================================================================
file_element_t *file_creer_element(movement_t movement_v, int promotion_v,
                                   int capture_v);
void file_destruire_element();

void file_list_add(file_list_t *file_list_v, movement_t movement_v,
                   int promotion_v, int capture_v);
file_element_t *file_list_extract(file_list_t *file_list_v);

file_list_t *file_creer_list();
void file_detruire_list(file_list_t *file_list_v);
int file_list_vide(file_list_t *file_list_v);
int file_taille(file_list_t *file_list_v);

// Je toucherai sa plus tard...
void file_thread();
movement_t file_unthread();

#endif
