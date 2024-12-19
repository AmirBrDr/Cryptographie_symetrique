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

#define maxCaractere 62

int total_cle;

struct cle{
    char cle[maxCaractere];
    float moy_freq_lettre;
    float mots_correctes;
};

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
void xor_chiffre(const unsigned char *msg, const unsigned char *key, unsigned char *output, size_t msg_len, size_t key_len) {
    for (size_t i = 0; i < msg_len; i++) {
        output[i] = msg[i] ^ key[i % key_len];  // Opération XOR
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

//Fonction qui calcule la distance entre la moyenne attendue et la moyennee du fichier decrypté
float moyenne_frequence_lettre(char *message_decrypte){
    float moyenne = 0;
    float occurence = 0;


    for(int i = 0; i <  26; i++){
        for(int j = 0; j < strlen(message_decrypte); j++){
            if(message_decrypte[j] == alphabet[i]){
                occurence++;
            }
        }
        printf("%c : %f occurences soit %f \n", alphabet[i], occurence, (occurence / strlen(message_decrypte)) * 100);

        moyenne = moyenne + pow((stat_thFr[i] - (occurence / strlen(message_decrypte)) * 100), 2.0);
        occurence = 0;
    }

    return moyenne;
}

//Fonction qui tri par ordre croissant de distance
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



int main(int argc, char *argv[]){

    if(argc != 2){
        fprintf(stderr, "Il y a des paramètres manquants.\n");
        exit(-1);
    }

    char *fichierEntree = argv[1];


    // Ouvrir le fichier crypté
    size_t taille;
    unsigned char *contenu = NULL;

    lire_fichier(fichierEntree, &contenu, &taille);


    //Mise en place de la variable contenant le xor

    char *message_decrypte = malloc(taille);


    //Boucle qui décrypte le fichier avec chaque clé, avant d'y attribuer une note
    for(int i = 0; i < total_cle; i++){
        //message_decrypte = xor_chiffre(contenu, tab_cle[i].cle, message_decrypte, taille );
        //tab_cle[i].moy_freq_lettre = moyenne_frequence_lettre(message_decrypte);
    }

    //tri_croissant(tab_cle, total_cle);



    //partie test
    printf("%f moyenne \n", moyenne_frequence_lettre(contenu));



    
}