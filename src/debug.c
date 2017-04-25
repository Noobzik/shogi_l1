#include "header/debug.h"
#include <stdio.h>

/** Info
 *  BLANC = 0
 *  NOIR  = 1
 */

/**debug_pile()
 * Permet d'afficher le contenue de la pile_element_t
 * @param:  game_t  *   -   g
 * @return: (void)
 */
void debug_pile         (game_t *g) {
  int                   i;
  pile_list_t    *      l;
  pile_element_t *      e;

  l = g->capture;

  printf("DEBUG | Pile\n");
  printf("Taille: %d\n", l->taille);

  if (pile_vide(l)) {
      printf("La pile ne contient rien\n");
      return;
  }

  for (e = l->suivant, i = 0; e != NULL; i++, e = e->suivant) {
      printf("Maillon %d | '", i);
      piece_afficher(e->piece);
      printf("' (Type: %d; Joueur: %d) Piece : \n", e->piece.type, e->piece.color);
  }


}

/**debug_file
 * Permet de faire la même chose que pile_vide
 * @param:  game_t  *   -   g
 * @return: (void)
 */
void debug_file         (game_t *g) {
    file_list_t *       l;
    file_element_t *    e;
    int                 i;

  l = g->file;
  printf("DEBUG | File\n");
  printf("Taille: %d\n", l->taille);

  if (file_list_vide(l)) {
      printf("La file ne contient rien\n");
      return;
  }

    for (e = l->debut, i = 0; e != NULL; i++, e = e->suivant) {
      printf("Maillon %d | ", i);
      printf("(%d;%d) ", e->movement.input.x, e->movement.input.y);
      printf("(%d;%d)\n", e->movement.output.x, e->movement.output.y);
    }
  printf("\n");
}

/** debug_cell
 * Permet d'inspecter une case
 * @param:    game_t *- g
 * @return:   (void)
 */
void debug_cell         (game_t *g, coordinate_t c) {

  printf("DEBUG | Cellule\n");

  if (!(c.x < 11 && c.y < 11)) {
      printf("Cette cellule est invalide.\n");
      return;
  }

  printf("Piece: ");
  piece_afficher(g->board[c.x][c.y]);
  printf(" (%d; %d)", c.x, c.y);
  printf("\nJoueur: %d", g->board[c.x][c.y].color);
  printf("Information sur la pièce \n"
  "Couleur: %d\n,Type: %d,Statut: %d",
  g->board[c.x][c.y].color, g->board[c.x][c.y].type, g->board[c.x][c.y].statut);

}

/**debug_partie_nouvelle
 * Permet de créer une partie customisé, focuse sur des cas précis de développement
 * @params: (void)
 * @return: game_t  *
 */
game_t * debug_partie_nouvelle  () {
  int                           x, y;
  game_t *                      res;

  res = partie_creer();
  res->capture = pile_create();
  res->file = file_creer_list();

  /** Info
   *  BLANC = 1
   *  NOIR  = 0
   */

  res->player = 0;

  /* Remplissage case vide */
  for (x = 0; x < 11; x++) {

    for (y = 0; y < 11; y++) {
      res->board[y][x] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
      res->board[y][x] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
    }
  }

  /* Pions */
  for (y = 1; y < 8; y++) {
    res->board[5][y] = piece_creer(NOIR, PION, NON_PROMU);
  }
  res->board[5][y] = piece_creer(BLANC, TOUR, NON_PROMU);

  return res;
}
