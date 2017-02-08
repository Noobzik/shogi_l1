# README #

### Projet Programmation Impérative - Guide de dev ###

## Quick summary ##

Repertoire Git pour le dévellopement du projet de programmation impérative, université Paris 13.
Dylan, Mohammed, Rakib, Yoann

# Version #
* **v0.0**

*En attente du sujet...*
*Le sujet devrait dispo sur l'ENT d'ici les vacances de Pâques*

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
/*
 * Description de la fonction
 * Elle retourne quoi ?
 */
```

Les fichiers header (\*h) doivent être situé dans un dossier src/header.
Un fichier unique loader.h sera à inclure dans chaque fichier c
```
#!c
# include "loader.h"
```


Lorsque vous push une modification, mettez un commentaire ce que vous avez modifié.code
Comme ça, s'il y a un problème, on peut revenir en arrière !!

# IMPORTANT #
**Si vous trouvez un bug, Signalez le sur le bitbucket, pour pas qu'on l'oublie.
L'objectif est 0 Warning + 0 Erreurs + 0 Probleme de mémoire (segmentation fault + pas le même nombre de malloc et free) + 0 bug / comportement fausse du programme**

On évite aussi de travailler sur le même ficher, pour éviter les conflits de push.

## Git ##

Je vous conseil d'installer GitKraken pour la gestion du repertoire en ligne. On veut limiter au maximum l'utilisation des clés USB

Procedure de mise en ligne des modification :
1. 'Stash' les fichiers que avez modifié
2. Ecrire un titre dans le commit + Un commentaire **IMPORTANT écriez pas de la merde, s'il y a un probème, on va galerer a revenir en arrière !**
3. Stage files /changes to Commit
4. Push
5. ???
6. Voila !

Pour récuperer les données :
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
