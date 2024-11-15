#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "dh_prime.h"

void print_usage() {
    printf("Usage: dh_gen_group -o <output_file> | -h\n");
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        print_usage();
        return 1;
    }

    const char *output_file = NULL;

    // Traitement des arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 && (i + 1) < argc) {
            output_file = argv[i + 1];
            i++; // Passer l'argument du fichier
        } else if (strcmp(argv[i], "-h") == 0) {
            print_usage();
            return 0;
        }
    }

    if (output_file == NULL) {
        fprintf(stderr, "Erreur : Aucun fichier de sortie spécifié.\n");
        return 1;
    }

    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires

    // Générer le nombre premier de Sophie Germain
    int cpt = 0;
    long p = genPrimeSophieGermain(1000, 10000, &cpt); // Définir une plage de recherche pour p
    if (p == 0) {
        fprintf(stderr, "Erreur lors de la génération du nombre premier.\n");
        return 1;
    }

    // Calculer le générateur
    long g = seek_generator(2, p); // Début à 2 pour le générateur

    // Écrire les résultats dans le fichier
    FILE *file = fopen(output_file, "w");
    if (file != NULL) {
        fprintf(file, "p = %ld\n", p);
        fprintf(file, "g = %ld\n", g);
        fclose(file);
        printf("Résultats écrits dans %s\n", output_file);
    } else {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier pour écrire les résultats.\n");
        return 1;
    }

    return 0;
}
