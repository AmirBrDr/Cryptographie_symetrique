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
    size_t taille = taille_fichier;
    //printf("taille message dans fonction : %d \n", taille);
    char car;
    
    for(size_t i = indiceClef; i < taille; i += tailleClef) { 
        car = message_entree[i] ^ caractere;
        if (!( isalnum(car) || car == ' ' || '\n')) {
            //printf("%d : %c invalide \n", indiceClef, caractere);
            return false;
        }
    }
    
    //printf("%d : %c valide = %c \n", indiceClef, caractere, car);
    return true;
}

/// @brief 
/// @param argc 
/// @param argv 
/// @return 
int main(int argc, char * argv[]){

    if(argc != 4){
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

    //temporaire
    printf("taille fichier : %ld \n", taille_contenu);

    if (taille_contenu != taille_fich_crypte) {
        perror("Erreur de lecture du fichier");
        free(contenu);
        fclose(file_crypté);
        exit(-1);
    }

    // Ajouter un caractère de fin de chaîne
    contenu[taille_contenu] = '\0';

    fclose(file_crypté);

    // Ouvrir le fichier de sortie
    FILE *fichier_crack = fopen(fichierSortie, "w");
    if (fichier_crack == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        free(contenu);
        exit(-1);
    }

    int tab[tailleClef][maxCaracteres];
    int compteur;

    // Générer les caractères possibles
    for(int index1 = 0; index1 < tailleClef; index1++){
        compteur = 0;
        for(int index2 = 0; index2 < maxCaracteres; index2++){

            if(charCorrect(contenu, alphabet[index2], tailleClef, index1, taille_contenu)){
                // Écrire le caractère dans le fichier de sortie
                fputc(alphabet[index2], fichier_crack);
                tab[index1][compteur] = alphabet[index2];
                compteur++;
            }
        }
        fputc('\n', fichier_crack);
    } 
    
    fclose(fichier_crack);
    free(contenu);

    return 0;
}
