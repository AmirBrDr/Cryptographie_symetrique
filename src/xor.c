#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

// Fonction de chiffrement et déchiffrement XOR
void xor_chiffre(const unsigned char *msg, const char *key, unsigned char *output, size_t msg_len, size_t key_len) {
    for (size_t i = 0; i < msg_len; i++) {
        output[i] = msg[i] ^ key[i % key_len];  // XOR with cyclic key
    }
}

// Fonction de génération aléatoire d'une clé alphanumérique
void gen_key(unsigned char *key, size_t key_len) {
    const char alphanum[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t alphanum_len = sizeof(alphanum) - 1;
    srand(time(NULL));
    for (size_t i = 0; i < key_len; i++) {
        key[i] = alphanum[rand() % alphanum_len]; // Sélectionner un caractère aléatoire
    }
    key[key_len] = '\0'; // Terminer la chaîne
}

// Fonction pour sauvegarder la clé dans un fichier
void save_key_to_file(const char *filename, const unsigned char *key) {
    FILE *file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "%s\n", key); // Écrire la clé suivie d'un saut de ligne
        fclose(file);
    } else {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier pour sauvegarder la clé.\n");
    }
}


//C'est pour faire un test
