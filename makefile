# Indication du compilateur
CC=gcc

# Flags du compilateur
CFLAGS = -g -Wall -pedantic -O3 -std=c11

# On force la derniere norme de compilation qui est C11

#Liste des fichiers *.o à rassembler en un executable
FICHIER = game.o piece.o file.o main.o

#Programme après la compilation
OUT = shogi

#Compilation séparé
CCSEP = $(CC) -c $(CFLAGS)

all:$(FICHIER)
	$(CC) $(FICHIER) $(CFLAGS) -lm -o $(OUT)

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

main.o:main.c
	$(CCSEP) main.c

# NE PAS TOUCHER EN BAS DE CETTE LIGNE
# Nettoie les junk .o et le prog, surement pour recompiler à zéro
clean:
	rm *.o
	rm $(OUT)

# Nettoie les fichier junk généré par Atom linter, en plus du prog, si vous avez touché au .h et .c en meme temps
clean-atom:
	rm *.o
	rm $(OUT)
	rm src/header/*.gch

# Sert a re-compiler à partir de 0
rebuild:clean all

# Sert a recompiler à partir de 0 et de lancer le prog
# Pour les flemmards et pour les big boss des 0 warning + 0 Erreurs
rebuild-run: rebuild
	./$(OUT)

# Compile le programme et execute directement, pour les flemmard du fleche haut
build-run:$(FICHIER)
	$(CC) $(FICHIER) $(CFLAGS) -lm -o $(OUT)
	./$(OUT)
