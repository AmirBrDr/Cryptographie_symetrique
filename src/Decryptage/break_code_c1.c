#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>

char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
int maxCaracteres = 62;
int tailleClef;

bool charCorrect(const char *message_entree, char caractere, int tailleClef, int indiceClef, int taille_fichier) {
    for (size_t i = indiceClef; i < taille_fichier; i += tailleClef) {
        char car = message_entree[i] ^ caractere;
        printf("XOR: message_entree[%zu] (%c) ^ caractere (%c) = %c (ASCII: %d)\n", i, message_entree[i], caractere, car, car);

        // Vérifier si le caractère est dans la plage imprimable
        if (!(isalnum(car) || ispunct(car) || isspace(car))) {
            printf("Caractère invalide : %c (ASCII: %d)\n", car, car);
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Il y a des paramètres manquants.\n");
        exit(-1);
    }

    tailleClef = atoi(argv[1]);
    char *fichierEntree = argv[2];
    char *fichierSortie = argv[3];

    // Ouvrir le fichier crypté
    FILE *file_crypté = fopen(fichierEntree, "rb");
    if (file_crypté == NULL) {
        perror("Erreur lors de l'ouverture du fichier crypté");
        exit(-1);
    }

    // Obtenir la taille du fichier
    fseek(file_crypté, 0, SEEK_END);
    long taille_fich_crypte = ftell(file_crypté);
    rewind(file_crypté);

    // Allouer de la mémoire
    char *contenu = malloc(taille_fich_crypte + 1);
    if (contenu == NULL) {
        perror("Échec de l'allocation de la mémoire");
        fclose(file_crypté);
        exit(-1);
    }

    // Lire le contenu du fichier
    size_t taille_contenu = fread(contenu, 1, taille_fich_crypte, file_crypté);
    if (taille_contenu != taille_fich_crypte) {
        perror("Erreur de lecture du fichier");
        free(contenu);
        fclose(file_crypté);
        exit(-1);
    }
    contenu[taille_contenu] = '\0';
    fclose(file_crypté);

    // Ouvrir le fichier de sortie
    FILE *fichier_crack = fopen(fichierSortie, "w");
    if (fichier_crack == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        free(contenu);
        exit(-1);
    }

    // Allouer dynamiquement le tableau des clés possibles
    char **tab = malloc(tailleClef * sizeof(char *));
    if (tab == NULL) {
        perror("Échec de l'allocation de la mémoire pour le tableau des clés");
        free(contenu);
        fclose(fichier_crack);
        exit(-1);
    }

    for (int i = 0; i < tailleClef; i++) {
        tab[i] = malloc(maxCaracteres * sizeof(char));
        if (tab[i] == NULL) {
            perror("Échec de l'allocation de la mémoire pour une colonne");
            for (int j = 0; j < i; j++) {
                free(tab[j]);
            }
            free(tab);
            free(contenu);
            fclose(fichier_crack);
            exit(-1);
        }
        memset(tab[i], 0, maxCaracteres * sizeof(char)); // Initialiser à 0
    }

    // Générer les clefs possibles
    for (int index1 = 0; index1 < tailleClef; index1++) {
        fprintf(fichier_crack, "Position %d : ", index1);
        int position = 0;
        for (int index2 = 0; index2 < maxCaracteres; index2++) {
            if (charCorrect(contenu, alphabet[index2], tailleClef, index1, taille_contenu)) {
                fprintf(fichier_crack, "%c", alphabet[index2]);
                tab[index1][position++] = alphabet[index2];
            }
        }
        fprintf(fichier_crack, "\n");
    }

    // Libérer la mémoire
    for (int i = 0; i < tailleClef; i++) {
        free(tab[i]);
    }
    free(tab);
    free(contenu);
    fclose(fichier_crack);

    return 0;
}
