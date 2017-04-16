# README #

### Projet Programmation Impérative 2017  Guide de développement ###
***
## Quick summary ##

Répertoire Git pour le développement du projet de programmation impérative, Université Paris 13.

*   Rakib Sheikh (NoobZik)
*   Ibrahim Kouyate
*   Emeric Bayard (Dryska)

**Le jeu à faire : Le Shôgi**
*Le sujet est disponible sur l'ENT, on attend la version définitif avant de l'inclure dans le répertoire*

*Le sujet est rempli de faute de règles, de fonctions*

*   Il est interdit d'annoncer à l'adversaire qu'il est en échec (Règle officiel)
*   La fin de partie se caractérise par la capture du Roi adverse

*Plus que 2 semaine pour boucler le projet*
## Mise en route ##

1.  Compilez le ficher avec make
2.  Démarrez le programme avec ./shogi
  *   *Dans le cas où vous avez Permission non accordée, faites*
  ```
  #!bash
  $ chmod +x ./shogi
  ```
3.   Pour connaitre la liste des commandes disponible
  ```
  #!bash
  help
  ```
4.  Pour démarrer le programme avec un fichier
  ```
  #!bash
  ./shogi "non_du_fichier_sans_extension"
  ```

***
# Version Actuelle: 0.4 Beta Release Candidate 2 #
## CHANGELOGS 0.4 Release candidate 2 ##
*   Les restrictions des fou promus et des tour promus ont été fixé.
*   D'important problème de mémoire sur la partie sauvegarde ont été fixé.
*   Une partie des noms des variables ont été simplifié
*   Implémentation de la démotion reserve, (Les pieces capturées promues sont dorénavant placé dans la réserve en changeant de statut vers non promu ET en changeant de couleur).
*   La fonction deplacement_apply à été transferé dans mouvement.c
*   La fonction annuler_deplacement à été transferé dans mouvement.c
*   Rajout de quelques commentaire un peu partout dans le projet.
*   Un probleme de création de la piece noir Tour Promu à été réglé (Oublie de return, ce qui cause la mise en attribution en pièce Argent promu).
*   **On est toujours à la Beta Release Candidate, Le projet est largement plus stable que la version précédente.**
*   Un rapport de projet est créer de manière temporaire.

#### CHANGELOGS 0.3 Release candidate 1 ####
*   Les problèmes de déplacements ont été fixé (Utilisez le signalement de bug si il persistent.
*   Il est désormais possible d'annuler les coups jouées.
*   La gestion des piles et des files sont finalisé.
*   Implémentation de la démotion, (Les pieces capturées promues sont dorénavant placé dans la réserve en changeant de statut vers non promu).
*   La fonction pour sauvegarder l'échiquier et son historique est desormais disponible.
*   La fonction pour charger l'échiquier est disponible, cependant, l'historique n'est pas encore developpé.
*   Passage en Beta Release Candidate, littéralement tout les warnings et les erreurs sont fixés, d'où cette appelation ***Beta Release Candidate***
*   Si le répertoire de sauvegarde n'existe pas, le programme le créera pour vous.


#### CHANGELOGS 0.2: ####
*   +Debug : ils permettent de passer le tour, inspecter la cellule, file et pile
*   +Mouvement : Les mouvements des pièce sont conforme au règlement officiel du shogi
*   +Restrictions : Cette partie permet d'eviter aux pièce de sauter les autres piece lors des déplacements
*   +Promotion des pièces conforme au règlement
*   +Les coordonnées d'arrivées ont maintenant une restriction exclusive sur l'échiquier
*   +Le parachutage des piece de la réserve est opérationnel et conforme au reglèment officiel du shogi
*   +Une aide visuel à été implémenté pour les déplacements
*   +Le makefile à été adapté en conformité avec le code source
*   Une fonction d'arret en cas de victoire par capture de la piece du ROI


#### CHANGELOGS 0.1: ####
*   Implémentation de 4 Fichier sources avec leur header respectif (game.c / file.c / pile.c /piece.c)
*   Remise en conformité au sujet en date du 21 mars 2017 v2

## Notes ##
*   Le main servira actuellement de test
***

## Ce qui reste à faire ##
*   Finalisation de la Gestion de sauvegardes / chargement de fichier
*   Commentaires sur tout les fonctions
*   Une interface graphique et éventuellement une intelligence artificiel
*   Replay_jouer, charge une partie avec une historique de coups jouer, anime la partie

La prochaine version se portera sur les bug smashing bros.

***
# Méthode de travail #
On va utiliser un répertoire privée en ligne sur ***bitbucket*** (Un alternative de GitHub)
L'avantage est de ne plus utiliser de clé USB : source de versions différentes et de problème de synchronisations.
On pourra déterminer plusieurs versions pas à pas, c'est à dire qu'il y aura une version pour les mouvements, une autre pour l'affichage etc etc...
On pourra retracer l'historique des modifications. Cette [historique se situe dans ce lien. On appelle ça un commit](https://bitbucket.org/asiat/prog_imp_2017/commits/)
Un gestion de [signalement de bug](https://bitbucket.org/asiat/prog_imp_2017/issues) qui vont prendre du temps à les régler, pour pas qu'on le zappe.
## Gitkraken ##
Il faut installer [GitKraken](https://www.gitkraken.com/) (ou autre logiciel de gestion de répertoire si vous êtes à l'aise) pour pouvoir mettre à jour le programme. (Les détails sont en bas).

Je ne sais pas si on peut lancer les programmes directement sur une clé usb sur les PC de la fac. J'invite à tester en [téléchargeant l'archive gzip](https://www.gitkraken.com/download/linux-gzip) et de l’exécuter à partir du terminal avec la commande. (Chez moi ça marche perso).

On peut aussi le faire par un terminal mais je m'y connais pas grand chose avec les commandes de git...
```
#!bash
./gitkraken
```
***
## Configuration ##

### Compilation du projet - Commandes make ###

Le fichier makefile fourni dans ce projet possède plusieurs options pour les développeurs. La liste complète se trouve ici.
La compilation se fait avec :
```
#!bash
make
```

Pour compiler à partir de 0
```
#!bash
make rebuild
```

Pour clean les fichiers résiduels
```
#!bash
make clean
```
Pour les utilisateurs atom avec Linter-gcc, si vous avez modifié les header ET les c. clean ne suffit pas. Pour ca, utilisez
```
#!bash
make clean-atom
```

Pour les flemmards, vous avez deux commandes qui sont :
```
#!bash
make build-run
```
Qui permet de compiler et de lancer directement le programme, pour les chaud qui codent sans warning et sans erreurs.

```
#!bash
make rebuild-run
```
Qui permet de recompiler a partir de 0, puis lance directement le programme, conseillé aux plus chaud qui codent sans warning et sans erreurs.

```
#!bash
make full-clean
```
Cette fonction permet de supprimer proprement les fichiers résiduel, y compris les fichiers de sauvegardes

```
#!bash
make full-clean-atom
```
Cette fonction permet de supprimer proprement les fichiers résiduel en incluant ceux de atom, y compris les fichiers de sauvegardes

***
## Méthodes de programmation ##

Il faut absolument **mettre des commentaires dans vos programmes**, surtout dans la rédaction de vos fonctions.
Le prototype des fonctions et des structures doivent être déclarées dans un fichier header (\*.h)

Les commentaires pour les fonctions auront le style suivant :
```
#!c
/** nom_de_la_fonction()
 * Description de la fonction
 * Complexité : Espace O() - Temps O()
 * @param type_t variable_v
 * @return "juste le type"
 */
```
Un exemple :
```
#!c
/** case_select(case_t case_v)
 * Permet de connaitre si la case actuelle peut être sélectionnable par l'utilisateur
 * en fonction du type de pièce. Fait appel aux autres fonctions déplacement_diagonal /
 * pion / vertical / horizontal
 * @param case_t case_v
 * @return int
 */
```
On fait pas de loader.h car c'est de la merde.

***
# IMPORTANT #
**Si vous trouvez un bug, [Signalez le](https://bitbucket.org/asiat/prog_imp_2017/issues?status=new&status=open) sur le bitbucket, pour pas qu'on l'oublie.
L'objectif est 0 Warning + 0 Erreurs + 0 Probleme de mémoire (segmentation fault + pas le même nombre de malloc et free) + 0 bug / comportement fausse du programme**


*   En cas de segmentation fault, Débuguez le programme avec ***valgrind*** voir même avec le flag ***-q*** pour ceux qui ont la flemme de lire/chercher (affiche seulement les erreur quand il y en a)

*   Pour signaler le(s) bug(s), reportez vous dans la partie [Signalement de bug](https://bitbucket.org/asiat/prog_imp_2017/issues?status=new&status=open)


On évite aussi de travailler sur le même ficher, pour éviter les conflits de push (push veut dire mettre en ligne les modifications vers le répertoire git).
***
Actuellement, la priorité actuelle est de créer une interface terminal le plus rapidement possible, pour qu'on puisse se focaliser sur les autres parties du projet


## Gestion du git ##
Je vous conseil d'installer GitKraken pour la gestion du répertoire en ligne. On veut limiter au maximum l'utilisation des clés USB

### Téléchargement du répertoire du projet ###

Il y a deux manière de récupérer les données du répertoire :

#### Méthode 1 ####
Récupérez vos identifiants SSH en haut à droite de la page du répertoire.
Ensuite dans GitKraken, Allez dans *Fichiers -> Cloner (Ou Crt+N)* puis clonez sur le pc.

#### Méthode 2 ####
Une autre méthode que j'ai découvert avec la nouvelle version, il suffit tout simplement de raccorder son compte bitbucket sur Gitkraken, ensuite vous pouvez directement cloner le répertoire depuis la liste des répertoires disponible.

Vous pouvez désormais commencer à modifier les codes sources du programme.

### Procédure de mise en ligne des modification (commit) : ####

1.   'Stage all changes' (ou quelque fichier) les fichiers que avez modifié
2.   Ecrire un titre dans le commit + Un commentaire
      *   ***IMPORTANT écrivez pas de la merde, s'il y a un problème, on va galérer a revenir en arrière !***

3.   Stage files /changes to Commit (Le bouton vert qu'il y a en bas du box)
4.   Push (Dans la bar d'outil au dessus, l'icone sous forme de flèche vers le haut avec un trait au dessus)
5.   ???
6.   Voila !

On pourra savoir qui a modifié/créer quoi, il y a un historique

**Note Important : Oubliez pas de supprimer les fichiers .o avant de push, la commande make clean est la pour ça.**

Pour récuperer/synchro les données vers la version récente:
-   Pull (icone avec une flèche vers le bas, un trait un bas, il se trouve sur la barre d'outils)

## Gestions des branches ##
*   La *branche principale* est le ***master*** C'est la version principale stable qui sera rendu aux profs.
*   Les *branches secondaires* seront à créer pour les development des fichiers
*   Avant de créer des fonctions, on doit impérativement utiliser les branches secondaires (Allez dans Branches -> Créer Branches -> Le nom de la branche)

Pour changer de branche :
Il y a jusqu'à double cliquer parmi la liste qui se situe à gauche
Je m'occupe de merge les modification vers la version principale après avoir testé.
***
Il faut aussi qu'on rédige un rapport pdf, il sera mis a disposition ici.
***
## Atom ##

Je vous conseil fortement de coder avec [Atom](http://atom.io) en installant les plugins suivant :

*   Pour auto-identer les programmes : [clang-format](https://atom.io/packages/clang-format)
*   Pour eviter de passer sur le terminal pour regler les Warning et les erreurs [linter](https://atom.io/packages/linter) et [linter-gcc](https://atom.io/packages/linter-gcc)
*   Pour vous retrouver dans le programme long [minimap](https://atom.io/packages/minimap)
*   Pour afficher les couleurs d'erreurs dans la minimap [minimap-linter](https://atom.io/packages/minimap-linter)
*   Pour clang-format, il faut avoir installé clang au préalable

```
#!bash
sudo apt-get install clang
```
***
### Who do I talk to? ###
*   Repo owner Rakib / NoobZik