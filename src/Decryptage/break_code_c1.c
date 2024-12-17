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
#include "break_code_c1.h"

char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
int maxCaracteres = 62;
int tailleClef;


bool charCorrect(const char *message_entree, char caractere, int tailleClef, int indiceClef, int taille_fichier) {
    size_t taille = taille_fichier;
    char car;
    
    for(size_t i = indiceClef; i < taille; i += tailleClef) { 
        car = message_entree[i] ^ caractere;
        if (!( isalnum(car) || car == ' ' || '\n')) {
            return false;
        }
    }
    
    //printf("%d : %c valide = %c \n", indiceClef, caractere, car);
    return true;
}

void break_code_c1(const unsigned char *message_entree, size_t taille_cle, char **cle_possibles, int *nombre_cle){
    int total_cle = 0;

    // Générer les clefs possibles
    for(int index1 = 0; index1 < taille_cle; index1++){
        for(int index2 = 0; index2 < maxCaracteres; index2++){
            if(charCorrect(message_entree, alphabet[index2], tailleClef, index1, taille_contenu)){
                cle_possibles[index1][index2] = alphabet[index2];
                total_cle++;
            }
        }
    }

    *nombre_cle = total_cle;

}
