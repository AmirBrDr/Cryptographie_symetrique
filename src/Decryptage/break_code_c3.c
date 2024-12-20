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
#include "xor.h"
#include "break_code_c3.h"
#define maxCaractere 62

int total_cle;




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

// Tri par ordre decroissant
void tri_decroissant(cle tab_cle[], int taille) {
    struct cle temp;
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (tab_cle[j].moy_freq_lettre < tab_cle[j + 1].moy_freq_lettre) {
                temp = tab_cle[j];
                tab_cle[j] = tab_cle[j + 1];
                tab_cle[j + 1] = temp;
            }
        }
    }
}



void break_code_c3(const unsigned char *message_entree, size_t taille_cle, size_t taille_message, struct cle *tab_cle_probables, int total_cle, char *fichier_dico){

    // Ouvrir le dictionnaire
    size_t taille_dico;
    unsigned char *contenu_dico = NULL;

    lire_fichier(fichier_dico, &contenu_dico, &taille_dico);

    //Peut être modifié si l'utilisateur le souhaite
    const char *separators = " ,.-!\n";



    char *message_decrypte = malloc(taille);


    //Boucle qui décrypte le fichier avec chaque clé, avant d'y attribuer le nombre de mots correctes
    for(int i = 0; i < total_cle; i++){
        message_decrypte = xor_chiffre(contenu, tab_cle_probables[i].cle, message_decrypte, taille );
        tab_cle_probables[i].mots_correctes = nombre_mots_correctes(message_decrytpe, contenu_dico, separators);
    }

    //fonction qui trie par ordre décroissant
    tri_croissant(tab_cle_probables[i], total_cle);



}