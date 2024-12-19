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
    int mots_correctes;
};

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

//Verifie si le mot est présent dans le dictionnaire
bool mot_present(char *mot, char *dico){
    char *present;
    present = strstr(dico, mot);

    if(present != NULL){
        return true;
    } else {
        return false;
    }
}

//retour le nombre de mots correctes avec un message dechiffré
int nombre_mots_correctes(char *message_decrypte, char *dico, const char *separators){
    char *token = strtok(message_decrypte, separators);
    int retour = 0;
    while(token != NULL){
        if(mot_present(token, dico)){
            retour++;
        }
        token = strtok(NULL, separators);
    }

    return retour;
}



int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Il y a des paramètres manquants.\n");
        exit(-1);
    }

    char *fichierEntree = argv[1];
    char *fichierDico = argv[2];


    // Ouvrir le fichier crypté
    size_t taille;
    unsigned char *contenu = NULL;

    lire_fichier(fichierEntree, &contenu, &taille);


    // Ouvrir le dictionnaire
    size_t taille_dico;
    unsigned char *contenu_dico = NULL;

    lire_fichier(fichierDico, &contenu_dico, &taille_dico);

    //Peut être modifié si l'utilisateur le souhaite
    const char *separators = " ,.-!\n";



    //Boucle qui décrypte le fichier avec chaque clé, avant d'y attribuer le nombre de mots correctes
    for(int i = 0; i < total_cle; i++){
        //message_decrypte = xor_chiffre(contenu, tab_cle[i].cle, message_decrypte, taille );
        //tab_cle[i].mots_correctes = nombre_mots_correctes(message_decrytpe, contenu_dico, separators);
    }

    //fonction qui trie par ordre décroissant


    //test

    struct cle test;
    test.mots_correctes = nombre_mots_correctes(contenu, contenu_dico, separators);

    printf("Il y a %d mots corrects \n", test.mots_correctes);



}