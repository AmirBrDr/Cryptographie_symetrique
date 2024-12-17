#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// XOR function with cyclic key
void xor_chiffre(const unsigned char *msg, const char *key, unsigned char *output, size_t msg_len, size_t key_len) {
    for (size_t i = 0; i < msg_len; i++) {
        output[i] = msg[i] ^ key[i % key_len];  // XOR with cyclic key
    }
}

// Function to read a file
void lire_fichier(const char *nom_fichier, unsigned char **contenu, size_t *taille) {
    FILE *fichier = fopen(nom_fichier, "rb");
    if (!fichier) {
        fprintf(stderr, "Erreur d'ouverture du fichier '%s' : %s\n", nom_fichier, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Get file size
    fseek(fichier, 0, SEEK_END);
    *taille = ftell(fichier);
    fseek(fichier, 0, SEEK_SET);

    // Allocate memory
    *contenu = malloc(*taille);
    if (!*contenu) {
        perror("Erreur d'allocation de mémoire");
        fclose(fichier);
        exit(EXIT_FAILURE);
    }

    // Read file content
    size_t bytes_read = fread(*contenu, 1, *taille, fichier);
    if (bytes_read != *taille) {
        fprintf(stderr, "Erreur de lecture : %zu octets lus au lieu de %zu.\n", bytes_read, *taille);
        free(*contenu);
        fclose(fichier);
        exit(EXIT_FAILURE);
    }
    fclose(fichier);
}

int main(int argc, char *argv[]) {
    size_t taille;
    const char *nom_fichier = "long_texte_crypte.txt";  // Fichier chiffré
    unsigned char *contenu = NULL;

    // Lire le fichier crypté
    lire_fichier(nom_fichier, &contenu, &taille);

    // Allouer un buffer pour le déchiffrement
    unsigned char *message_decrypte = malloc(taille + 1);
    if (!message_decrypte) {
        perror("Erreur d'allocation pour le déchiffrement");
        free(contenu);
        exit(EXIT_FAILURE);
    }

    // Clé pour le XOR
    const char *key = "taratata";
    size_t key_len = strlen(key);

    // Déchiffrer le message
    xor_chiffre(contenu, key, message_decrypte, taille, key_len);

    // Ajouter un null terminator pour afficher comme une chaîne
    message_decrypte[taille] = '\0';

    // Écrire le message déchiffré dans un fichier de sortie
    FILE *output_file = fopen("message_dechiffre.txt", "wb");
    if (!output_file) {
        perror("Erreur d'ouverture du fichier de sortie");
        free(contenu);
        free(message_decrypte);
        exit(EXIT_FAILURE);
    }

    fwrite(message_decrypte, 1, taille, output_file);
    fclose(output_file);

    printf("Message déchiffré écrit dans 'message_dechiffre.txt'.\n");

    // Libérer la mémoire
    free(contenu);
    free(message_decrypte);

    return 0;
}
