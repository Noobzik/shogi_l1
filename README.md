# README #

### Projet Programmation Impérative - Guide de développement ###

## Quick summary ##

Repertoire Git pour le développement du projet de programmation impérative, Université Paris 13.
Dylan, Mohammed, Rakib, Yoann

# Version #
* **v0.0**

*En attente du sujet...*
*Le sujet devrait disponible le lundi 20 mars*

*1 mois pour boucler le projet*

### How do I get set up? ###

* Summary of set up

Il faut installer GitKraken pour pouvoir mettre à jour le prog. (Les détails sont en bas).

* Configuration

* Compilation du projet - Commandes make

Le fichier makefile fourni dans ce projet possède plusieurs options pour les dévellopeurs. La liste complète ce trouve ici.

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
Demandez un merge vers le master

### Méthode de programmation ###

Il faut absolument mettre des commentaires dans vos programme, surtout dans la rédaction de vos fonctions.
Le prototype des fonctions et des structures doivent être déclarées dans un fichier Header ( * .h)

Les commentaires pour les fonctions auront le style suivant :
```
#!c
/**
 * Description de la fonction
 * @param
 * @return
 */
```

Un exemple :

```
#!c
/**
 * Permet de connaitre si la case actuelle peut être selectionnable par l'utilisateur
 * en fonction du type de piece. Fait appel aux autres fonctions déplacement_diagonal / 
 * pion / vertical / horizontal
 * @param une case
 * @return un entier
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
**Si vous trouvez un bug, Signalez le sur le bitbucket, pour pas qu'on l'oublie.
L'objectif est 0 Warning + 0 Erreurs + 0 Probleme de mémoire (segmentation fault + pas le même nombre de malloc et free) + 0 bug / comportement fausse du programme**

* En cas de segmentation fault, Debuggez le prog avec ** *valgrind* **
* Pour signaler le(s) bug(s), reportez vous dans la partie Signalement de bug

On évite aussi de travailler sur le même ficher, pour éviter les conflits de push.


## Gestions des branches ##

* La *branche principale* est le ** *master* ** C'est la version principale stable qui sera rendu aux profs.
* Les *branches secondaires* seront à créer pour les development des fichiers

Actuellement, la priorité actuelle est de créer une interface terminal le plus rapidement possible, pour qu'on puisse se focaliser sur les autres parties du projet

## Git ##

Je vous conseil d'installer GitKraken pour la gestion du repertoire en ligne. On veut limiter au maximum l'utilisation des clés USB

Procedure de mise en ligne des modification :


1. 'Stash' les fichiers que avez modifié
2. Ecrire un titre dans le commit + Un commentaire 
   * **IMPORTANT écrivez pas de la merde, s'il y a un probème, on va galerer a revenir en arrière !**
3. Stage files /changes to Commit
4. Push
5. ???
6. Voila !


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

* Writing tests

* Code review
* Other guidelines

### Who do I talk to? ###

* Repo owner Rakib / NoobZik