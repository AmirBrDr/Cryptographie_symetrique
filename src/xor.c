#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

// Fonction de chiffrement et déchiffrement XOR
void xor(const unsigned char *msg, const unsigned char *key, unsigned char *output, size_t msg_len, size_t key_len) {
    for (size_t i = 0; i < msg_len; i++) {
        output[i] = msg[i] ^ key[i % key_len];  // Opération XOR
    }
}

// Fonction de génération aléatoire d'une clé alphanumérique
void gen_key(unsigned char *key, size_t key_len) {
    const char alphanum[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t alphanum_len = sizeof(alphanum) - 1;

    for (size_t i = 0; i < key_len; i++) {
        key[i] = alphanum[rand() % alphanum_len]; // Sélectionner un caractère aléatoire
    }
    key[key_len] = '\0'; // Terminer la chaîne
}

int main() {
    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL)); // Utiliser l'heure actuelle comme graine pour donner à chaque fois un nombre aleatoire different

    // Exemple de message et de clé
    unsigned char msg[] = "Projet avance Equipe 6";
    unsigned char key[20]; // Clé de longueur maximale de 20
    gen_key(key, 10); // Générer une clé aléatoire de 10 caractères

    size_t msg_len = strlen((char *)msg);
    size_t key_len = strlen((char *)key);
    
    // Allocation de mémoire pour le résultat chiffré
    unsigned char *encrypted = (unsigned char *)malloc(msg_len + 1);
    unsigned char *decrypted = (unsigned char *)malloc(msg_len + 1);

    // Chiffrement
    xor(msg, key, encrypted, msg_len, key_len);
    encrypted[msg_len] = '\0'; // Terminer la chaîne

    // Déchiffrement
    xor(encrypted, key, decrypted, msg_len, key_len);
    decrypted[msg_len] = '\0'; // Terminer la chaîne

    // Affichage des résultats
    printf("Message original: %s\n", msg);
    printf("Clé générée: %s\n", key);
    printf("Message chiffré (hex): ");
    for (size_t i = 0; i < msg_len; i++) {
        printf("%02x ", encrypted[i]);
    }
    printf("\n");
    printf("Message déchiffré: %s\n", decrypted);

    // Libération de la mémoire
    free(encrypted);
    free(decrypted);

    return 0;
}
