/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 21:04:41 by NoobZik           #+#    #+#             */
/*   Updated: 2017/04/30 21:04:42 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "header/display.h"

/* Variable globale (Limite du code C, pas d'argument optionnel)*/
//coordinate_t COORDINATE_NULL = {42, 42};
coordinate_t COORDINATE_NULL_DISPLAY = {42,42};

void show_menu            (int game_command_dev){
  if (game_command_dev) {
    printf("PASS                  Passe le tour du joueur.\n");
    printf("FILE                  Affiche les donnes contenu dans la "
           "file.\n");
    printf("PILE                  Affiche les donnes contenu dans la "
           "pile.\n");
    printf("CELL                  Inspecter une cellule.\n");
  }

  else {
    printf("DEV                   Pour activer les command developpeur.\n");
  }
  printf("\n");

  /* Classic command */
  printf("SURREND               Declarer forfait.\n");
  printf("MOVE                  Selectionner le deplacement d'une piece.\n");
  printf("BACK                  Restaurer le deplacement precedent.\n");
  printf("SAVE                  Sauvegarder la partie.\n");
  printf("EXIT                  Quitter le jeu.\n");
  printf("42,42                 Pour désélectionner une pièce,(Seulement quand on demande des coordonées)\n");
  return;
}

int dev_enabler           (int game_command_dev){
  if (game_command_dev == 0) {
    printf("Les commandes developpeur sont active,\nSaisissez 'help' pour "
           "en savoir plus sur les commandes.\n");
    game_command_dev = 1;
  } else {
    printf("Les commandes developpeur ont été désactivé.\n");
    game_command_dev = 0;
  }
  return game_command_dev;
}

coordinate_t cell_input   (game_t *g, coordinate_t g_i){
  printf("Saisir les coordonnees d'une piece:\n");
  afficher_echiquier(g, COORDINATE_NULL_DISPLAY);
  printf("\n\n\n");
  g_i = saisie_case();
  return g_i;
}

void surrend              (game_t *g){
  printf("Le joueur ");

  if (g->player == 0) {
    printf("Blanc");
  } else if (g->player == 1) {
    printf("Noir");
  }

  printf(" a gagner la partie par abandon.\n");
}

void unknow_cmd           (char const *game_command){
  printf("'%s' n'est pas reconnu comme une commande,\nsaisissez 'help' "
         "pour en savoir plus sur les commandes.\n",
         game_command);
}

void print__select_piece  (){
  printf("Saisir les coordonnées d'une piece:\n");
}

void selected_piece       (game_t *g, coordinate_t g_i)  {
  printf("Vous avez selectionner la piece '");
  piece_afficher(g->board[g_i.x][g_i.y]);
  printf("' de coordonnees (%d;%d) du joueur ", g_i.x, g_i.y);
  printf("%d.", g->board[g_i.x][g_i.y].color);
  printf("\n\nSi vous voulez parachuter un pion et qu'il n'y a pas "
          "d'étoile, "
          "saisissez 42, 42\n");
  printf("\nSaisir les coordonnees du movement:\n");
}
