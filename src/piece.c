#include "header/piece.h"
#include <stdio.h>
#include <stdlib.h>

/** Création de piece
 * La couleur représente soit J1, soit J0
 * Le type de piece est la liste enuméré des type (ex : Fou)
 * Le statut determine si cette piece est promu ou non
 * Complexité : O(1) Temps et Espace
 * Parameters:
 * @param piece_color_e  - piece_color_v
 *        piece_type_e   - piece_type_v
 *        piece_statut_e - piece_statut_v
 *
 * @return struct piece_s
 */
piece_t piece_creer(piece_color_e piece_color_v, piece_type_e piece_type_v,
                    piece_statut_e piece_statut_v) {

  piece_t res;

  /* Initialiser */
  res.color = piece_color_v;
  res.type = piece_type_v;
  res.statut = piece_statut_v;

  return res;
}

/** Couleur de piece
 * Renvoie tout simplement la couleur de piece
 * Complexité : O(1) Pour Espace / Temps
 * Parameters:
 * @param    piece_t - piece_v
 * @return int
 */
int piece_couleur(piece_t piece_v) { return piece_v.color; }

/** Identification de piece
 * piece identifier
 * Description : En fonction du caractère, renvoie la piece associé
 * Complexite : O(1) Espace et Temps
 * Parameters:
 * @param    char - caracter_v
 * @return struct piece_s
 */
piece_t piece_identifier(char caracter_v) {
  if (caracter_v <= 'z' && caracter_v >= 'a') {
    switch (caracter_v) {
      // Non promu joueur 0
      {
      case 'p':
        return piece_creer(BLANC, PION, NON_PROMU);
      }
      {
      case 'l':
        return piece_creer(BLANC, LANCIER, NON_PROMU);
      }
      {
      case 'n':
        return piece_creer(BLANC, CAVALIER, NON_PROMU);
      }
      {
      case 'b':
        return piece_creer(BLANC, FOU, NON_PROMU);
      }
      {
      case 'r':
        return piece_creer(BLANC, TOUR, NON_PROMU);
      }
      {
      case 's':
        return piece_creer(BLANC, SILVER, NON_PROMU);
      }
      {
      case 'g':
        return piece_creer(BLANC, GOLD, NON_PROMU);
      }
      {
      case 'k':
        return piece_creer(BLANC, ROI, NON_PROMU);
      }
      // Promu Joueur 2
      {
      case 'd':
        return piece_creer(BLANC, PION_PROMU, PROMU);
      }
      {
      case 'j':
        return piece_creer(BLANC, LANCIER_PROMU, PROMU);
      }
      {
      case 'c':
        return piece_creer(BLANC, CAVALIER_PROMU, PROMU);
      }
      {
      case 'f':
        return piece_creer(BLANC, FOU_PROMU, PROMU);
      }
      {
      case 't':
        return piece_creer(BLANC, TOUR_PROMU, PROMU);
      }
      {
      case 'a':
        return piece_creer(BLANC, SILVER_PROMU, PROMU);
      }
    }
  } else {
    switch (caracter_v) {
      // Non Promu Joueur 1
      {
      case 'P':
        return piece_creer(NOIR, PION, NON_PROMU);
      }
      {
      case 'L':
        return piece_creer(NOIR, LANCIER, NON_PROMU);
      }
      {
      case 'N':
        return piece_creer(NOIR, CAVALIER, NON_PROMU);
      }
      {
      case 'B':
        return piece_creer(NOIR, FOU, NON_PROMU);
      }
      {
      case 'R':
        return piece_creer(NOIR, TOUR, NON_PROMU);
      }
      {
      case 'S':
        return piece_creer(NOIR, SILVER, NON_PROMU);
      }
      {
      case 'G':
        return piece_creer(NOIR, GOLD, NON_PROMU);
      }
      {
      case 'K':
        return piece_creer(NOIR, ROI, NON_PROMU);
      }
      // Promu Joueur 1
      {
      case 'D':
        return piece_creer(NOIR, PION_PROMU, PROMU);
      }
      {
      case 'J':
        return piece_creer(NOIR, LANCIER_PROMU, PROMU);
      }
      {
      case 'C':
        return piece_creer(NOIR, CAVALIER_PROMU, PROMU);
      }
      {
      case 'F':
        return piece_creer(NOIR, FOU_PROMU, PROMU);
      }
      {
      case 'T':
        return piece_creer(NOIR, TOUR_PROMU, PROMU);
      }
      {
      case 'A':
        return piece_creer(NOIR, SILVER, PROMU);
      }
    }
  }

  return piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
}

/** Detections de piece
 * Permet d'associer chaque numéro à chaque piece en fonction du type enuméré
 * et de la couleur de piece
 * Parameters:
 * @param    piece_t - piece_v
 * @return char
 */
char piece_caractere(piece_t piece_v) {
  if (piece_couleur(piece_v) == 0) {
    switch (piece_v.type) {
      {
      case ROI:
        return 'k';
      }
      {
      case TOUR:
        return 'r';
      }
      {
      case FOU:
        return 'b';
      }
      {
      case GOLD:
        return 'g';
      }
      {
      case SILVER:
        return 's';
      }
      {
      case CAVALIER:
        return 'n';
      }
      {
      case LANCIER:
        return 'l';
      }
      {
      case PION:
        return 'p';
      }
      {
      case PION_PROMU:
        return 'd'; // PION PROMU
      }
      {
      case LANCIER_PROMU:
        return 'j'; // LANCIER PROMU
      }
      {
      case CAVALIER_PROMU:
        return 'c'; // CAVALIER PROMU
      }
      {
      case FOU_PROMU:
        return 'f'; // FOU PROMU
      }
      {
      case TOUR_PROMU:
        return 't'; // TOUR PROMU
      }
      {
      case SILVER_PROMU:
        return 'a'; // SILVER PROMU
      }
      {
      case SELECT:
        return '*';
      }
      {
      default:
        return '.';
      }
    }
  } else {
    switch (piece_v.type) {
      {
      case ROI:
        return 'K';
      }
      {
      case TOUR:
        return 'R';
      }
      {
      case FOU:
        return 'B';
      }
      {
      case GOLD:
        return 'G';
      }
      {
      case SILVER:
        return 'S';
      }
      {
      case CAVALIER:
        return 'N';
      }
      {
      case LANCIER:
        return 'L';
      }
      {
      case PION:
        return 'P';
      }
      {
      case PION_PROMU:
        return 'D'; // PION PROMU
      }
      {
      case LANCIER_PROMU:
        return 'J'; // LANCIER PROMU
      }
      {
      case CAVALIER_PROMU:
        return 'C'; // CAVALIER PROMU
      }
      {
      case FOU_PROMU:
        return 'F'; // FOU PROMU
      }
      {
      case TOUR_PROMU:
        return 'T'; // TOUR PROMU
      }
      {
      case SILVER_PROMU:
        return 'A'; // SILVER PROMU
      }
      {
      case SELECT:
        return '*';
      }
      {
      default:
        return '.';
      }
    }
  }

  return '.';
}

/** piece displayer
 * piece displayer
 * Permet d'afficher tout simplement la piece sur l'echiquier
 * Complexite : O(1) pour Espace et Temps
 * Parameters:
 * @param    piece_t - piece_v
 * @return NADA
 */
void piece_afficher(piece_t piece_v) { printf("%c", piece_caractere(piece_v)); }

/** promote_grant
 *  Permet de promovoir la piece
 *  @params:    piece_t     -   piece
 *  @return:    void
 */
void promote_grant(piece_t *p) {
  switch (p->type) {
    {
    case PION:
      p->type = PION_PROMU;
      p->statut = PROMU;
      break;
    }
    {
    case LANCIER:
      p->type = LANCIER_PROMU;
      p->statut = PROMU;
      break;
    }
    {
    case CAVALIER:
      p->type = CAVALIER_PROMU;
      p->statut = PROMU;
      break;
    }
    {
    case FOU:
      p->type = FOU_PROMU;
      p->statut = PROMU;
      break;
    }
    {
    case TOUR:
      p->type = TOUR_PROMU;
      p->statut = PROMU;
      break;
    }
    {
    case SILVER:
      p->type = SILVER_PROMU;
      p->statut = PROMU;
      break;
    }
  default:
    break;
  }
}

/** demote_grant
 *  Permet de dé-promovoir la piece en changeant de couleur (Pour la reserve)
 *  @params:    piece_t     -   piece
 *  @return:    void
 */
piece_t demote_grant_reserve(piece_t p) {
  if (p.color == BLANC) {
    switch (p.type) {
      {
      case PION_PROMU:
        p.color = NOIR;
        p.type = PION;
        p.statut = NON_PROMU;
        break;
      }
      {
      case LANCIER_PROMU:
        p.color = NOIR;
        p.type = LANCIER;
        p.statut = NON_PROMU;
        break;
      }
      {
      case CAVALIER_PROMU:
        p.color = NOIR;
        p.type = CAVALIER;
        p.statut = NON_PROMU;
        break;
      }
      {
      case FOU_PROMU:
        p.color = NOIR;
        p.type = FOU;
        p.statut = NON_PROMU;
        break;
      }
      {
      case TOUR_PROMU:
        p.color = NOIR;
        p.type = TOUR;
        p.statut = NON_PROMU;
        break;
      }
      {
      case SILVER_PROMU:
        p.color = NOIR;
        p.type = SILVER;
        p.statut = NON_PROMU;
        break;
      }
    default:
      break;
    }
  } else if (p.color == NOIR) {
    switch (p.type) {
      {
      case PION_PROMU:
        p.color = BLANC;
        p.type = PION;
        p.statut = NON_PROMU;
        break;
      }
      {
      case LANCIER_PROMU:
        p.color = BLANC;
        p.type = LANCIER;
        p.statut = NON_PROMU;
        break;
      }
      {
      case CAVALIER_PROMU:
        p.color = BLANC;
        p.type = CAVALIER;
        p.statut = NON_PROMU;
        break;
      }
      {
      case FOU_PROMU:
        p.color = BLANC;
        p.type = FOU;
        p.statut = NON_PROMU;
        break;
      }
      {
      case TOUR_PROMU:
        p.color = BLANC;
        p.type = TOUR;
        p.statut = NON_PROMU;
        break;
      }
      {
      case SILVER_PROMU:
        p.color = BLANC;
        p.type = SILVER;
        p.statut = NON_PROMU;
        break;
      }
    default:
      break;
    }
  }
  return p;
}

/** Démote la piece sans changer de couleur pour annuler_deplacement*/
piece_t demote_grant(piece_t p) {
  switch (p.type) {
    {
    case PION_PROMU:
      p.type = PION;
      p.statut = NON_PROMU;
      break;
    }
    {
    case LANCIER_PROMU:
      p.type = LANCIER;
      p.statut = NON_PROMU;
      break;
    }
    {
    case CAVALIER_PROMU:
      p.type = CAVALIER;
      p.statut = NON_PROMU;
      break;
    }
    {
    case FOU_PROMU:
      p.type = FOU;
      p.statut = NON_PROMU;
      break;
    }
    {
    case TOUR_PROMU:
      p.type = TOUR;
      p.statut = NON_PROMU;
      break;
    }
    {
    case SILVER_PROMU:
      p.type = SILVER;
      p.statut = NON_PROMU;
      break;
    }
  default:
    break;
  }
  return p;
}

/** switch_color
 * permet de changer de couleur avant de le mettre dans la reserve
 * @params:  piece_t   -   p
 * @return:  piece_t
 */
piece_t switch_color(piece_t p) {
  if (p.color == BLANC)
    p.color = NOIR;
  else if (p.color == NOIR)
    p.color = BLANC;
  return p;
}
