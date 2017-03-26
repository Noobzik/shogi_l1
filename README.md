# README #

### Projet Programmation Impérative - Guide de développement ###

## Quick summary ##

Repertoire Git pour le développement du projet de programmation impérative, Université Paris 13.
* Rakib

**Le jeu à faire : Le Shôgi**
*Le sujet est disponible sur l'ENT, on attend la version définitif avant de l'inclure dans le répertoire*

*1 mois pour boucler le projet*

# Version : 0.1 #

# CHANGELOGS : #
* Implémentation de 4 Fichier sources avec leur header respectif(game.c / file.c / pile.c /piece.c)
* Remise en conformité au sujet en date du 21 mars 2017 v2
## Notes ##
* Le main servira actuellement de test
## Changements à venir ##
* Détails des commentaires dans certaines parties du programme
* Introductions aux validation des mouvement et de leurs restrictions (Avec implémentation de l'aide visuel SELECT)

## Ce qui reste à faire ##
* Mouvements avec leurs validations et leurs restrictions
* La gestions des sauvegardes des fichiers


# Méthodes de travail #

On va utiliser un repertoire privée en ligne sur bitbucket (Un alternative de GitHub)
L'avantage est de ne plus utiliser de clées USB : source de versions différentes et de problème de synchronisations
On pourra determiner plusieurs versions pas à pas, c'est à dire qu'il y aura une version pour les mouvement, une autre pour l'affichage etc etc...
On pourra retracer l'historique des modifications
Un gestion de signalement de bug qui vont prendre du temps à les régler, pour pas qu'on le zape

## Gitkraken ##


Il faut installer GitKraken (ou autre logiciel de gestion de repertoire si vous êtes à l'aise) pour pouvoir mettre à jour le prog. (Les détails sont en bas).

## Configuration, MAKEFILE ##

## Compilation du projet - Commandes make ##

Le fichier makefile fourni dans ce projet possède plusieurs options pour les développeurs. La liste complète se trouve ici.

La compilation se fait avec :
```
#!bash
make
```

Pour compiler a partir de 0

```
#!bash
make rebuild
```

Pour clean les ficihers résiduels

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
Qui permet de compiler et de lancer directement le programme, pour les chaud qui codent sans warning et sans erreurs

```
#!bash
make rebuild-run
```
Qui permet de recompiler a partir de 0, puis lance directement le programme, conseillé aux plus chaud qui codent sans warning et sans erreurs

* Deployment instructions
Demandez un merge vers le master c'est moi qui m'en occupe

## Méthodes de compilations ##

Il faut absolument mettre des commentaires dans vos programmes, surtout dans la rédaction de vos fonctions.
Le prototype des fonctions et des structures doivent être déclarées dans un fichier Header ( * .h)

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
/**
 * Permet de connaitre si la case actuelle peut être selectionnable par l'utilisateur
 * en fonction du type de piece. Fait appel aux autres fonctions déplacement_diagonal /
 * pion / vertical / horizontal
 * @param case_t case_v
 * @return int
 */
```

Les fichiers header (\*h) doivent être situé dans un dossier src/header.
Un fichier unique loader.h sera à inclure dans chaque fichier c
```
#!c
#include "loader.h"
```


Lorsque vous push une modification, mettez un commentaire ce que vous avez modifié.code
Comme ça, s'il y a un problème, on peut revenir en arrière !!

# IMPORTANT #
**Si vous trouvez un bug, [Signalez le]https://bitbucket.org/asiat/prog_imp_2017/issues?status=new&status=open
 sur le bitbucket, pour pas qu'on l'oublie.
L'objectif est 0 Warning + 0 Erreurs + 0 Probleme de mémoire (segmentation fault + pas le même nombre de malloc et free) + 0 bug / comportement fausse du programme**


* En cas de segmentation fault, Debuggez le prog avec ** *valgrind* ** voir même avec le flag -q pour ceux qui ont la flemme de lire/chercher (affiche seulement les erreur quand il y en a)

* Pour signaler le(s) bug(s), reportez vous dans la partie [Signalez de bug]https://bitbucket.org/asiat/prog_imp_2017/issues?status=new&status=open


On évite aussi de travailler sur le même ficher, pour éviter les conflits de push.


## Gestions des branches ##

* La *branche principale* est le ** *master* ** C'est la version principale stable qui sera rendu aux profs.
* Les *branches secondaires* seront à créer pour les development des fichiers


* Avant de creer des fonctions, on doit impérativement utiliser les branches secondaires (Allez dans Branches -> Créer Branches -> Le nom de la branche


Actuellement, la priorité actuelle est de créer une interface terminal le plus rapidement possible, pour qu'on puisse se focaliser sur les autres parties du projet

## Git ##

Je vous conseil d'installer GitKraken pour la gestion du repertoire en ligne. On veut limiter au maximum l'utilisation des clés USB

Pour pouvoir télécharger les données du projet, récuperez vos identifiants SSH en haut à droite de la page du répértoire.
Ensuite dans GitKraken, Allez dans Fichiers -> Cloner (Ou Crt+N) puis clonez sur le pc.

Vous pouvez désormais commencer à modifier les programmes

Procedure de mise en ligne des modification :

1. 'Stage all changes' (ou quelque fichier) les fichiers que avez modifié
2. Ecrire un titre dans le commit + Un commentaire
   * **IMPORTANT écrivez pas de la merde, s'il y a un probème, on va galerer a revenir en arrière !**
3. Stage files /changes to Commit
4. Push
5. ???
6. Voila !

On pourra savoir qui a modifié/créer quoi, il y a un historique

**Note Important : Oubliez pas de supprimer les fichiers .o avant de push, la commande make clean est la pour ça. **

Pour récuperer/synchro les données vers la version récente:
- Pull

Pour changer de branche :
Il y a jusqu'à double cliquer

Je m'occupe de merge les modification vers la version principale après avoir testé.


Il faut aussi qu'on rédige un rapport pdf, il sera mis a disposition ici.

## Atom ##

Je vous conseil fortement de coder avec [Atom](http://atom.io) en installant les plugins suivant :

clang-format
Pour auto-identer les programmes

Linter
Linter-gcc
Pour eviter de passer sur le terminal pour regler les Warning et les erreurs

Pour vous retrouver dans le programme long
minimap
linter-minimap

Pour clang-format, il faut avoir installé clang
```
#!bash
sudo apt-get install clang
```

### Who do I talk to? ###

* Repo owner Rakib / NoobZik