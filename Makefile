all: heuristique

heuristique:
	gcc main.c -o build/heuristique
	gcc genetique_projet.c -o build/genetique
