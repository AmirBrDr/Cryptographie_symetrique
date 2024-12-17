#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include "cbc.h"  // Assurez-vous d'inclure votre fichier d'en-tête
#include "xor.h"

// Flux de log (par défaut stderr)
FILE *log_flux = NULL;

// Fonction pour afficher l'aide et les options du programme
void afficher_aide() {
    fprintf(log_flux ? log_flux : stdout,
            "Utilisation : symcrypt -i <fichier_entree> -o <fichier_sortie> -k <cle> | -f <fichier_cle> -m <methode> -v <fichier_iv> [-l <fichier_log>]\n");
    fprintf(log_flux ? log_flux : stdout,
            "Options :\n"
            "  -i <fichier_entree>   Fichier contenant le texte en clair (obligatoire)\n"
            "  -o <fichier_sortie>   Fichier de sortie pour le texte chiffré (obligatoire)\n"
            "  -k <cle>              Clé pour le chiffrement/déchiffrement (obligatoire)\n"
            "  -f <fichier_cle>      Fichier contenant la clé (alternative à -k)\n"
            "  -m <methode>          Méthode (xor, cbc-crypt, cbc-uncrypt, masque)\n"
            "  -v <fichier_iv>       Fichier du vecteur d'initialisation (obligatoire pour CBC)\n"
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

    if (log_flux) fprintf(log_flux, "Lecture du fichier '%s' réussie, taille : %zu octets\n", nom_fichier, *taille);
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

    if (log_flux) fprintf(log_flux, "Écriture dans le fichier '%s' réussie, taille : %zu octets\n", nom_fichier, taille);
}

int main(int argc, char *argv[]) {
    const char *fichier_entree = NULL;
    const char *fichier_sortie = NULL;
    const char *fichier_cle = NULL;
    const char *cle_directe = NULL;
    const char *methode = NULL;
    const char *fichier_iv = NULL;
    const char *fichier_log = NULL;

    unsigned char *vecteur_init = NULL;
    unsigned char *cle = NULL;
    size_t taille_iv = 0;
    size_t taille_cle = 0;

    int option;
    while ((option = getopt(argc, argv, "i:o:k:f:m:v:l:h")) != -1) {
        switch (option) {
            case 'i':
                fichier_entree = optarg;
                break;
            case 'o':
                fichier_sortie = optarg;
                break;
            case 'k':
                cle_directe = optarg;
                break;
            case 'f':
                fichier_cle = optarg;
                break;
            case 'm':
                methode = optarg;
                break;
            case 'v':
                fichier_iv = optarg;
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

    if (log_flux) fprintf(log_flux, "Début du processus de cryptographie...\n");

    if (!fichier_entree || !fichier_sortie || (!cle_directe && !fichier_cle) || (!cle_directe && !fichier_cle && strcmp(methode, "mask") != 0) 
        || (!fichier_iv && strcmp(methode, "cbc-crypt") == 0) || (!fichier_iv && strcmp(methode, "cbc-uncrypt") == 0)|| !methode) {
            
        fprintf(stderr, "Erreur : Arguments obligatoires manquants.\n");
        if (log_flux) fprintf(log_flux, "Erreur : Arguments obligatoires manquants.\n");
        afficher_aide();
        return EXIT_FAILURE;
    }

    unsigned char *message_entree = NULL;
    size_t taille_entree = 0;
    lire_fichier(fichier_entree, &message_entree, &taille_entree);

    unsigned char *message_sortie = malloc(taille_entree + TAILLE_BLOC);
    if (!message_sortie) {
        perror("Erreur d'allocation de mémoire pour le message de sortie");
        if (log_flux) fprintf(log_flux, "Erreur d'allocation de mémoire pour le message de sortie\n");
        free(message_entree);
        free(vecteur_init);
        return EXIT_FAILURE;
    }

    if (fichier_cle) {
        lire_fichier(fichier_cle, &cle, &taille_cle);
        if (log_flux) fprintf(log_flux, "Clé lue depuis le fichier '%s'\n", fichier_cle);
    } else {
        taille_cle = strlen(cle_directe);
        cle = (unsigned char *)cle_directe;
        if (log_flux) fprintf(log_flux, "Clé spécifiée en ligne de commande\n");
    }

    if (strcmp(methode, "xor") == 0) {

        xor_chiffre(message_entree, cle, message_sortie, taille_entree, strlen(cle));
        if (log_flux) fprintf(log_flux, "Chiffrement XOR effectué.\n");

    } else if (strcmp(methode, "cbc-crypt") == 0) {

        lire_fichier(fichier_iv, &vecteur_init, &taille_iv);

        if (taille_iv != TAILLE_BLOC) {
            fprintf(stderr, "Erreur : Le vecteur d'initialisation doit faire %d octets.\n", TAILLE_BLOC);
            if (log_flux) fprintf(log_flux, "Erreur : Le vecteur d'initialisation doit faire %d octets.\n", TAILLE_BLOC);
            free(vecteur_init);
            return EXIT_FAILURE;
        }
        cbc_chiffrement(message_entree, taille_entree, cle, vecteur_init, message_sortie);

        if (log_flux) fprintf(log_flux, "Chiffrement CBC effectué.\n");

    } else if (strcmp(methode, "cbc-uncrypt") == 0) {

        lire_fichier(fichier_iv, &vecteur_init, &taille_iv);
        if (taille_iv != TAILLE_BLOC) {
            fprintf(stderr, "Erreur : Le vecteur d'initialisation doit faire %d octets.\n", TAILLE_BLOC);
            if (log_flux) fprintf(log_flux, "Erreur : Le vecteur d'initialisation doit faire %d octets.\n", TAILLE_BLOC);
            free(vecteur_init);
            return EXIT_FAILURE;
        }
        cbc_dechiffrement(message_entree, taille_entree, cle, vecteur_init, message_sortie);

        if (log_flux) fprintf(log_flux, "Déchiffrement CBC effectué.\n");
        
    } else if (strcmp(methode, "mask") == 0) {
        // Générer une clé aléatoire si la méthode est mask
        cle = malloc(taille_entree + 1);

        if (!cle) {
            perror("Erreur d'allocation de mémoire pour la clé générée");
            free(message_entree);
            free(message_sortie);
            return EXIT_FAILURE;
        }

        gen_key(cle, taille_entree);  // Utiliser la fonction pour générer la clé aléatoire
        xor_chiffre(message_entree, cle, message_sortie, taille_entree, strlen(cle));
        if (log_flux) fprintf(log_flux, "Chiffrement XOR effectué.\n");
        save_key_to_file(fichier_cle, cle);  // Sauvegarder la clé dans key.txt

        if (log_flux){
            fprintf(log_flux, "Écriture dans le fichier '%s' réussie, taille : %zu octets\n", fichier_cle, (unsigned long)taille_entree);
        } 


    } else {

        fprintf(stderr, "Erreur : Méthode inconnue '%s'.\n", methode);
        if (log_flux) fprintf(log_flux, "Erreur : Méthode inconnue '%s'.\n", methode);
        free(message_entree);
        free(message_sortie);
        free(vecteur_init);
        if (fichier_cle) free(cle);
        return EXIT_FAILURE;
        
    }

    ecrire_fichier(fichier_sortie, message_sortie, taille_entree);

    if (log_flux) fprintf(log_flux, "Processus terminé avec succès.\n");

    free(message_entree);
    free(message_sortie);
    free(vecteur_init);
    if (fichier_cle) free(cle);

    if (log_flux != stderr) fclose(log_flux);

    return EXIT_SUCCESS;
}
