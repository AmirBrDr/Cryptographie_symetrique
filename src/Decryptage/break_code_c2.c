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
#include <math.h>
#include "break_code_c2.h"


#define maxCaractere 62

int total_cle;


/// français
float stat_thFr[26] = {9.42, 1.02, 2.64, 3.39, 15.87, 0.95, 1.04, 0.77, 8.41, 0.89,
		0.00, 5.34, 3.24, 7.15,  5.14, 2.86, 1.06, 6.46, 7.90, 7.26,
		6.24, 2.15, 0.00, 0.30, 0.24, 0.32};

//anglais de a à z
  float stat_thEn[26] = {8.167, 1.492, 2.782,4.253,12.702,2.228,2.015,6.094,6.966,0.153,
        0.772,4.025,2.406,6.749,7.507,1.929,0.095,5.987,6.327,9.056,
        2.758,0.978,2.36,0.15,1.974,0.074};

//alphabet
char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";



// Fonction de chiffrement et déchiffrement XOR
void xor_chiffre(const unsigned char *msg, const char *key, unsigned char *output, size_t msg_len, size_t key_len) {
    for (size_t i = 0; i < msg_len; i++) {
        output[i] = msg[i] ^ key[i % key_len];  // XOR with cyclic key
    }
}

// Fonction pour lire un fichier
void lire_fichier(const char *nom_fichier, unsigned char **contenu, size_t *taille) {
    FILE *fichier = fopen(nom_fichier, "rb");
    if (!fichier) {
        fprintf(stderr, "Erreur d'ouverture du fichier '%s' : %s\n", nom_fichier, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Obtenir la taille du fichier
    fseek(fichier, 0, SEEK_END);
    *taille = ftell(fichier);
    fseek(fichier, 0, SEEK_SET);
    
    // Allouer de la mémoire pour le contenu du fichier
    *contenu = malloc(*taille);
    if (!*contenu) {
        perror("Erreur d'allocation de mémoire");
        fclose(fichier);
        exit(EXIT_FAILURE);
    }
    
    // Lire le fichier dans le tampon
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


void tri_croissant(struct cle *tab_cle, int taille) {
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


void break_code_c2(const unsigned char *message_entree, size_t taille_cle, size_t taille_message, char **cle_possibles, struct cle *tab_cle_probables, int total_cle){

    //Mise en place de la variable contenant le xor

    char *message_decrypte = malloc(taille_message + 16);


    //Boucle qui décrypte le fichier avec chaque clé, avant d'y attribuer une note
    for(int i = 0; i < total_cle; i++){
        xor_chiffre(message_entree, cle_possibles[i], message_decrypte, taille_message, taille_cle );
        tab_cle_probables[i].moy_freq_lettre = moyenne_frequence_lettre(message_decrypte, taille_message);
    }

    //tri par ordre croissant
    tri_croissant(tab_cle_probables, total_cle);
}