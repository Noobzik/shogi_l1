/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 21:04:57 by NoobZik           #+#    #+#             */
/*   Updated: 2017/04/30 21:04:57 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "header/piece.h"
#include <stdio.h>
#include <stdlib.h>
/********************************** INDEX *************************************/
/*    1) Bloc de pièces (sujet)
 *    2) Bloc de deplacement_valide et valide_win
 *    3) Bloc de gestion de promtion pour annuler / reserve.
 */

/** piece_creer();
 * La couleur représente soit J1, soit J0
 * Le type de piece est la liste enuméré des type (ex : Fou)
 * Le statut determine si cette piece est promu ou non
 * Complexité : O(1) Temps et Espace
 * Parameters:
 * @param piece_color_e  - c
 *        piece_type_e   - t
 *        piece_statut_e - s
 *
 * @return piece_t
 */
piece_t piece_creer         (piece_color_e c, piece_type_e t, piece_statut_e s) {
  piece_t                   res;

  res.color = c;
  res.type = t;
  res.statut = s;

  return res;
}

/** Couleur de piece
 * Renvoie tout simplement la couleur de piece
 * Complexité : O(1) Pour Espace / Temps
 * Parameters:
 * @param    piece_t - p
 * @return   int
 */
int piece_couleur           (piece_t p) {
    return p.color;
}

/** piece_identifier();
 * piece identifier
 * Description : En fonction du caractère, renvoie la piece associé
 * Complexite : O(1) Espace et Temps
 * @param    char - caracter_v
 * @return   piece_t
 */
piece_t piece_identifier    (char caracter_v) {
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

/** piece_caractere
 * Permet d'associer chaque numéro à chaque piece en fonction du type enuméré
 * et de la couleur de piece
 * Parameters:
 * @param       piece_t - p
 * @return      char
 */
char piece_caractere        (piece_t p) {
  if (piece_couleur(p) == 0) {
    switch (p.type) {
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
    switch (p.type) {
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
 * Permet d'afficher tout simplement la piece sur l'echiquier
 * Complexite : O(1) pour Espace et Temps
 * Parameters:
 * @param    piece_t - p
 * @return   (void)
 */
void piece_afficher         (piece_t p) {
    printf("%c", piece_caractere(p));
}

/* Cette partie ci dessous est rédigé par Rakib Sheikh (NoobZik)*/
/** promote_grant
 *  Permet de promovoir la piece
 *  @params:    piece_t     -   p
 *  @return:    (void)
 */
void promote_grant          (piece_t *p) {
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

/** demote_grant_reserve
 *  Permet de dé-promovoir la piece en changeant de couleur (Pour la reserve)
 *  @params:    piece_t     -   p
 *  @return:    (void)
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

/** demote_grant
 * Démote la piece sans changer de couleur pour annuler_deplacement
 * @param:  piece_t     -   p
 * @return: piece_t
 */
piece_t demote_grant        (piece_t p) {
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
piece_t switch_color        (piece_t p) {
  if (p.color == BLANC)
    p.color = NOIR;
  else if (p.color == NOIR)
    p.color = BLANC;
  return p;
}

/** piece_cmp_reserve
 *  Permet de comparer deux pieces de couleur différente
 *  Pour la gestion de la réserve en annulation
 *  @params : piece_t           -   p
 *  @return : int
 */
int piece_cmp_reserve       (piece_t p1, piece_t p2){
  if(!(p1.color == p2.color))
    if(p1.type == p2.type)
      if(p1.statut == p2.statut)
        return 1;
  return 0;
}
