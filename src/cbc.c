#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cbc.h"
#define TAILLE_BLOC 16

// Fonction de chiffrement CBC (Cipher Block Chaining)
void cbc_chiffrement(const unsigned char *message, size_t message_len, const unsigned char *cle, const unsigned char *vi, unsigned char *message_chiffrer) {
    // Calcul de la longueur ajustée pour un remplissage multiple de TAILLE_BLOC
    size_t padded_len = message_len;
    if (padded_len % TAILLE_BLOC != 0) {
        padded_len += TAILLE_BLOC - (padded_len % TAILLE_BLOC);
    }

    // Copie du vecteur d'initialisation (IV) dans `bloc_precedent`
    unsigned char bloc_precedent[TAILLE_BLOC];
    memcpy(bloc_precedent, vi, TAILLE_BLOC);

    // Boucle sur chaque bloc du message
    for (size_t i = 0; i < padded_len; i += TAILLE_BLOC) {
        unsigned char bloc[TAILLE_BLOC] = {0};  // Initialisation du bloc avec des zéros

        // Copie du message dans le bloc actuel (jusqu'à TAILLE_BLOC ou le reste du message)
        size_t copy_len = (i + TAILLE_BLOC <= message_len) ? TAILLE_BLOC : message_len - i;
        memcpy(bloc, message + i, copy_len);

        // Étape d'initialisation XOR entre le bloc actuel et le bloc précédent
        for (size_t j = 0; j < TAILLE_BLOC; j++) {
            bloc[j] ^= bloc_precedent[j];
        }

        // Chiffrement du bloc en utilisant la fonction `xor_chiffre` et la clé
        xor_chiffre(bloc, cle, message_chiffrer + i, TAILLE_BLOC, strlen(cle));

        // Mise à jour de `bloc_precedent` avec le bloc chiffré pour l'itération suivante
        memcpy(bloc_precedent, message_chiffrer + i, TAILLE_BLOC);
    }
}

// Fonction de déchiffrement CBC (Cipher Block Chaining)
void cbc_dechiffrement(const unsigned char *message_chiffre, size_t message_len, const unsigned char *cle, const unsigned char *vi, unsigned char *message_dechiffre) {
    unsigned char bloc_precedent[TAILLE_BLOC];
    memcpy(bloc_precedent, vi, TAILLE_BLOC);  // Copie du vecteur d'initialisation (IV) dans `bloc_precedent`

    // Boucle sur chaque bloc du message chiffré
    for (size_t i = 0; i < message_len; i += TAILLE_BLOC) {
        unsigned char bloc[TAILLE_BLOC];
        unsigned char bloc_intermediaire[TAILLE_BLOC];

        // Déchiffrement du bloc en utilisant `xor_chiffre` et la clé
        xor_chiffre(message_chiffre + i, cle, bloc_intermediaire, TAILLE_BLOC, strlen(cle));

        // XOR entre `bloc_intermediaire` et le `bloc_precedent` pour obtenir le texte clair
        for (size_t j = 0; j < TAILLE_BLOC; j++) {
            bloc[j] = bloc_intermediaire[j] ^ bloc_precedent[j];
        }

        // Copie du bloc déchiffré dans le message final
        memcpy(message_dechiffre + i, bloc, TAILLE_BLOC);

        // Mise à jour de `bloc_precedent` pour la prochaine itération
        memcpy(bloc_precedent, message_chiffre + i, TAILLE_BLOC);
    }
}
