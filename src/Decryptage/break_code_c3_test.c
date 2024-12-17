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
#include "break_code_c3_test.h"

#define maxCaractere 62

int total_cle;

struct cle{
    char cle[maxCaractere];
    float moy_freq_lettre;
    int mots_correctes;
};


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

/* Verifie si le mot est présent dans le dictionnaire
 * - `mot` : le mot à chercher
 * - `dico` : le dictionnaire
 */
bool mot_present(char *mot, char *dico){
    char *present;
    present = strstr(dico, mot);

    if(present != NULL){
        return true;
    } else {
        return false;
    }
}

/* Retourne le nombre de mots correctes avec un message déchiffré 
 * - `message_decrypte` : le message déchiffré
 * - `dico` : le dictionnaire
 * - `separators` : les séparateurs
*/
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
    // Ouvrir le fichier
    size_t taille;
    char *nom_fichier = "long_texte.txt";
    unsigned char *contenu = NULL;

    lire_fichier(nom_fichier, &contenu, &taille);


    // Ouvrir le dictionnaire
    size_t taille_dico;
    char *nom_dico = "dicoFrSA.txt";
    unsigned char *contenu_dico = NULL;

    lire_fichier(nom_dico, &contenu_dico, &taille_dico);

    //Peut être modifié si l'utilisateur le souhaite
    const char *separators = " ,.-!\n";

    //variable temporaire, doit être récupérée avec breakc2
    struct cle tab_cle[total_cle];


    char *message_decrypte = malloc(taille);


    //Boucle qui décrypte le fichier avec chaque clé, avant d'y attribuer le nombre de mots correctes
    for(int i = 0; i < total_cle; i++){
        //message_decrypte = xor_chiffre(contenu, tab_cle[i].cle, message_decrypte, taille );
        //tab_cle[i].mots_correctes = nombre_mots_correctes(message_decrytpe, contenu_dico, separators);
    }

    //fonction qui trie par ordre décroissant


    //test

    struct cle test;
    test.mots_correctes = nombre_mots_correctes(contenu, contenu_dico, separators);

    printf("%d \n", test.mots_correctes);



}