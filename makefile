# Projet imcopilable avec C90, n'essayez pas de compiler sur windows... J'en ai fais les frais
# Indication du compilateur
CC=gcc

#Objectif 0 WARNING, donc inclusion de tout les warnings possibles, Wall est trop gentil...
WARNING :=  -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
		-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
		-Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
		-Wuninitialized -Wconversion -Wstrict-prototypes
# Flags du compilateur
CFLAGS = -g -O3 -fpic $(WARNING) -std=c11

# On force la derniere norme de compilation qui est C11

#Liste des fichiers *.o à rassembler en un executable
FICHIER = game.o piece.o file.o pile.o mouvement.o debug.o restriction.o sauvegardes.o main.o

#Programme après la compilation
OUT = shogi

#Compilation séparé
CCSEP = $(CC) -c $(CFLAGS)

all:$(FICHIER)
	$(CC) $(FICHIER) $(CFLAGS) -o $(OUT)

# Ici les dépendances de compilation de chaque ficher
# La commande à utiliser est $(CCSEP) ficher.c
# Exemple
#cercle.o : cercle.c
#	$(CCSEP) cercle.c

game.o:src/game.c
	$(CCSEP) src/game.c

piece.o:src/piece.c
	$(CCSEP) src/piece.c

file.o:src/file.c
	$(CCSEP) src/file.c

pile.o:src/pile.c
	$(CCSEP) src/pile.c

mouvement.o:src/mouvement.c
	$(CCSEP) src/mouvement.c

restriction.o:src/restriction.c
	$(CCSEP) src/restriction.c

debug.o:src/debug.c
	$(CCSEP) src/debug.c

sauvegardes.o:src/sauvegardes.c
	$(CCSEP) src/sauvegardes.c

main.o:main.c
	$(CCSEP) main.c

# NE PAS TOUCHER EN BAS DE CETTE LIGNE
# Nettoie les junk .o et le prog, surement pour recompiler à zéro
clean:
	rm *.o
	rm $(OUT)

# Nettoie les fichier junk généré par Atom linter, en plus du prog, si vous avez touché au .h et .c en meme temps
clean-atom:
	rm src/header/*.gch
	rm *.o
	rm $(OUT)

# Nettoie littéralement tout
full-clean:clean
	rm -rf partie
	rm -rf plateaux

# Nettoie littéralement tout en plus des fichiers résiduel atom
full-clean-atom:clean-atom
	rm -rf partie
	rm -rf plateaux

# Sert a re-compiler à partir de 0
rebuild:clean all

# Sert a recompiler à partir de 0 et de lancer le prog
# Pour les flemmards et pour les big boss des 0 warning + 0 Erreurs
rebuild-run: rebuild
	./$(OUT)

# Compile le programme et execute directement, pour les flemmard du fleche haut
build-run:$(FICHIER)
	$(CC) $(FICHIER) $(CFLAGS) -o $(OUT)
	./$(OUT)
