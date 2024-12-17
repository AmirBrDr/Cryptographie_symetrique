#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include "xor.h"
#include "break_code_c1.h"
#include "break_code_c2.h"
#include "break_code_c3.h"

#define maxCaracteres 62

// Flux de log (par défaut stderr)
FILE *log_flux = NULL;



// Fonction pour afficher l'aide et les options du programme
void afficher_aide() {
    fprintf(log_flux ? log_flux : stdout,
            "Utilisation : break_code -i <fichier_entree> -m <methode> -k <longueur_cle> [-d <fichier_dictionnaire>] [-l <fichier_log>]\n");
    fprintf(log_flux ? log_flux : stdout,
            "Options :\n"
            "  -i <fichier_entree>   Fichier contenant le texte crypté (obligatoire)\n"
            "  -m <methode>          Méthode (c1, all)\n"
            "  -k <cle>              Longueur de la clé ayant servie à crypter le texte (obligatoire)\n"
            "  -d <fichier_cle>      Fichier contenant le dictionnaire (obligatoire si all)\n"
            "  -l <fichier_log>      Fichier de log (optionnel, par défaut stderr)\n"
            "  -h                    Afficher ce message d'aide\n");
}

// Fonction pour lire le contenu d'un fichier
void lire_fichier(const char *nom_fichier, unsigned char **contenu, size_t *taille) {
    FILE *fichier = fopen(nom_fichier, "rb");
    if (!fichier) {
        fprintf(stderr, "Erreur d'ouverture du fichier '%s' : %s\n", nom_fichier, strerror(errno));
        if (log_flux) fprintf(log_flux, "Erreur d'ouverture du fichier '%s' : %s\n", nom_fichier, strerror(errno));
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
        if (log_flux) fprintf(log_flux, "Erreur d'allocation de mémoire pour le contenu du fichier\n");
        exit(EXIT_FAILURE);
    }
    
    // Lire le fichier dans le tampon
    fread(*contenu, 1, *taille, fichier);
    fclose(fichier);

    if (log_flux) fprintf(log_flux, "Lecture du fichier '%s' réussie, taille : %lu octets\n", nom_fichier, (long unsigned int)taille);
}

// Fonction pour écrire le contenu dans un fichier
void ecrire_fichier(const char *nom_fichier, const unsigned char *contenu, size_t taille) {
    FILE *fichier = fopen(nom_fichier, "wb");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier de sortie");
        if (log_flux) fprintf(log_flux, "Erreur d'ouverture du fichier de sortie '%s'\n", nom_fichier);
        exit(EXIT_FAILURE);
    }
    
    fwrite(contenu, 1, taille, fichier);
    fclose(fichier);

    if (log_flux) fprintf(log_flux, "Écriture dans le fichier '%s' réussie, taille : %lu octets\n", nom_fichier, (long unsigned int)taille);
}


int main(int argc, char *argv[]) {
    const char *fichier_entree = NULL;
    const char *methode = NULL;
    const char *cle = NULL; 
    char *fichier_dico = NULL;
    const char *fichier_log = NULL;

    size_t taille_cle = 0;

    int option;
    while ((option = getopt(argc, argv, "i:m:k:d:l:h")) != -1) {
        switch (option) {
            case 'i':
                fichier_entree = optarg;
                break;
            case 'm':
                methode = optarg;
                break;
            case 'k':
                cle = optarg;
                break;
            case 'd':
                fichier_dico = optarg;
                break;
            case 'l':
                fichier_log = optarg;
                break;
            case 'h':
                afficher_aide();
                return 0;
            default:
                afficher_aide();
                return EXIT_FAILURE;
        }
    }

    if (fichier_log) {
        log_flux = fopen(fichier_log, "w");
        if (!log_flux) {
            fprintf(stderr, "Erreur d'ouverture du fichier de log '%s'\n", fichier_log);
            return EXIT_FAILURE;
        }
    } else {
        log_flux = stderr;
    }

    if (!fichier_entree || !methode || (!cle) || (!fichier_dico && (strcmp(methode, "all") == 0))) {
            
        fprintf(stderr, "Erreur : Arguments obligatoires manquants.\n");
        if (log_flux) fprintf(log_flux, "Erreur : Arguments obligatoires manquants.\n");
        afficher_aide();
        return EXIT_FAILURE;
    }

    if (log_flux) fprintf(log_flux, "Début du processus de decryptage...\n");

    unsigned char *message_entree = NULL;
    size_t taille_entree = 0;
    lire_fichier(fichier_entree, &message_entree, &taille_entree);
    taille_cle = atoi(cle);
    int nombre_cle;

    char cle_possibles[taille_cle][maxCaracteres];
    memset(cle_possibles, 0, sizeof(cle_possibles));  


    if (strcmp(methode, "c1") == 0) {

        break_code_c1(message_entree, taille_cle, cle_possibles, &nombre_cle);
        if (log_flux) {
            fprintf(log_flux, "La liste des clés possibles a été générée : \n");

            for(int i = 0; i < taille_cle; i++){
                fprintf(log_flux, "%s \n", cle_possibles[i]);
            }

        }

    } else if (strcmp(methode, "all") == 0){

        break_code_c1(message_entree, taille_cle, cle_possibles, &nombre_cle);
        if (log_flux) {
            fprintf(log_flux, "La liste des clés possibles a été générée : \n");

            for(int i = 0; i < taille_cle; i++){
                fprintf(log_flux, "%s \n", cle_possibles[i]);
            }
        }

        struct cle tab_cle_probables[10];

        if (log_flux) fprintf(log_flux, "Début du tri en fonction de la distance statistique des lettres \n");
        break_code_c2(message_entree, taille_cle,taille_entree, cle_possibles, tab_cle_probables);


        if (log_flux) fprintf(log_flux, "Début du tri en fonction du nombre de mots valides \n");
        break_code_c3(message_entree, taille_cle,taille_entree, tab_cle_probables);

        if (log_flux) fprintf(log_flux, "La clé la plus probable est : %s \n", tab_cle_probables[0].cle);


    } else {
        fprintf(stderr, "Erreur : Méthode inconnue '%s'.\n", methode);
        if (log_flux) fprintf(log_flux, "Erreur : Méthode inconnue '%s'.\n", methode);
        free(message_entree);
        if (fichier_dico) free(fichier_dico);
        return EXIT_FAILURE;
    }

    if (log_flux) fprintf(log_flux, "Processus terminé avec succès.\n");

    free(message_entree);
    if (fichier_dico) free(fichier_dico);
    if (log_flux != stderr) fclose(log_flux);

    return EXIT_SUCCESS;

}