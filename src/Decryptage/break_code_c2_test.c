#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <ctype.h>
#include "break_code_c2.h"

#define maxCaractere 62

int total_cle;

struct cle {
    char cle[maxCaractere];
    float moy_freq_lettre;
};

/// Statistiques pour la langue française
float stat_thFr[26] = {9.42, 1.02, 2.64, 3.39, 15.87, 0.95, 1.04, 0.77, 8.41, 0.89,
                       0.00, 5.34, 3.24, 7.15, 5.14, 2.86, 1.06, 6.46, 7.90, 7.26,
                       6.24, 2.15, 0.00, 0.30, 0.24, 0.32};

// Alphabet
char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

// Fonction de chiffrement et déchiffrement XOR
void xor_chiffre(const unsigned char *msg, const char *key, unsigned char *output, size_t msg_len, int key_size) {
    for (size_t i = 0; i < msg_len; i++) {
        output[i] = msg[i] ^ key[i % key_size];  // XOR avec la clé cyclique
    }
}

// Fonction pour lire un fichier
void lire_fichier(const char *nom_fichier, unsigned char **contenu, size_t *taille) {
    FILE *fichier = fopen(nom_fichier, "rb");
    if (!fichier) {
        fprintf(stderr, "Erreur d'ouverture du fichier '%s' : %s\n", nom_fichier, strerror(errno));
        exit(EXIT_FAILURE);
    }

    fseek(fichier, 0, SEEK_END);
    *taille = ftell(fichier);
    fseek(fichier, 0, SEEK_SET);

    *contenu = malloc(*taille);
    if (!*contenu) {
        perror("Erreur d'allocation de mémoire");
        fclose(fichier);
        exit(EXIT_FAILURE);
    }

    fread(*contenu, 1, *taille, fichier);
    fclose(fichier);
}


float moyenne_frequence_lettre(const unsigned char *message, size_t taille) {
    int occurences[26] = {0};
    int total_lettres = 0;

    // Compter les occurrences des lettres alphabétiques
    for (size_t i = 0; i < taille; i++) {
        if (isalpha(message[i])) {
            occurences[tolower(message[i]) - 'a']++;
            total_lettres++;
        }
    }

    // Retourner une grande distance si aucune lettre n'est trouvée
    if (total_lettres == 0) {
        return 1e6; // Une distance arbitraire très grande pour éliminer cette clé
    }

    // Calculer la moyenne des écarts
    float moyenne = 0.0;
    for (int i = 0; i < 26; i++) {
        float freq_obs = (occurences[i] / (float)total_lettres) * 100.0;
        moyenne += pow(stat_thFr[i] - freq_obs, 2);
    }

    return sqrt(moyenne);
}


void tri_croissant(struct cle tab_cle[], int taille) {
    struct cle temp;
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (tab_cle[j].moy_freq_lettre > tab_cle[j + 1].moy_freq_lettre) {
                temp = tab_cle[j];
                tab_cle[j] = tab_cle[j + 1];
                tab_cle[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int tailleClef = 3;  // Exemple temporaire, la taille de la clé

    // Exemple de tableau de caractères possibles
    char tab_car_possible[3][maxCaractere] = {"abc", "12", "xyz"};

    // Calcul du nombre total de clés possibles
    total_cle = 1;
    for (int i = 0; i < tailleClef; i++) {
        total_cle *= strlen(tab_car_possible[i]);
    }

    struct cle tab_cle[total_cle];

    // Génération des clés
    int index = 0;
    for (int i = 0; i < strlen(tab_car_possible[0]); i++) {
        for (int j = 0; j < strlen(tab_car_possible[1]); j++) {
            for (int k = 0; k < strlen(tab_car_possible[2]); k++) {
                snprintf(tab_cle[index].cle, tailleClef + 1, "%c%c%c",
                         tab_car_possible[0][i], tab_car_possible[1][j], tab_car_possible[2][k]);
                index++;
            }
        }
    }

    // Lire le fichier chiffré
    unsigned char *contenu;
    size_t taille;
    lire_fichier("long_texte.txt", &contenu, &taille);

    unsigned char *message_decrypte = malloc(taille);

    // Tester chaque clé
    for (int i = 0; i < total_cle; i++) {
        xor_chiffre(contenu, tab_cle[i].cle, message_decrypte, taille, tailleClef);
        tab_cle[i].moy_freq_lettre = moyenne_frequence_lettre(message_decrypte, taille);
    }

    // Trier les clés
    tri_croissant(tab_cle, total_cle);

    // Afficher les 10 premières clés
    printf("Top 10 des clés avec la plus faible distance :\n");
    for (int i = 0; i < 10 && i < total_cle; i++) {
        printf("Clé : %s, Distance : %.2f\n", tab_cle[i].cle, tab_cle[i].moy_freq_lettre);
    }

    free(contenu);
    free(message_decrypte);
    return 0;
}
