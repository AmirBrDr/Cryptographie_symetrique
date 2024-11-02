#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xor.h"
#define TAILLE_BLOC 16


void cbc_chiffrement(const unsigned char *message, const unsigned char *cle, const unsigned char *vi, unsigned char *message_chiffrer) {
    size_t message_len = strlen((const char *)message);
    size_t padded_len = message_len;

    if (padded_len % TAILLE_BLOC != 0) {
        padded_len += TAILLE_BLOC - (padded_len % TAILLE_BLOC);
    }

    unsigned char bloc_precedent[TAILLE_BLOC];
    memcpy(bloc_precedent, vi, TAILLE_BLOC);  

    for (size_t i = 0; i < padded_len; i += TAILLE_BLOC) {
        unsigned char bloc[TAILLE_BLOC] = {0}; 
        strncpy((char *)bloc, (const char *)(message + i), TAILLE_BLOC);  

        for (size_t j = 0; j < TAILLE_BLOC; j++) {
            bloc[j] ^= bloc_precedent[j];
        }

        xor_chiffre(bloc, cle, message_chiffrer + i, TAILLE_BLOC);


        memcpy(bloc_precedent, message_chiffrer + i, TAILLE_BLOC);
    }
}

void cbc_dechiffrement(unsigned char *message_chiffre, unsigned char *cle, unsigned char *vi, unsigned char *message_dechiffre) {
    unsigned char bloc_precedent[TAILLE_BLOC];
    memcpy(bloc_precedent, vi, TAILLE_BLOC);  

    for (size_t i = 0; i < strlen((const char *)message_chiffre); i += TAILLE_BLOC) {
        unsigned char bloc[TAILLE_BLOC];
        unsigned char bloc_intermediaire[TAILLE_BLOC];

        xor_chiffre(message_chiffre + i, cle, bloc_intermediaire, TAILLE_BLOC);

        xor_chiffre(bloc_intermediaire, bloc_precedent, bloc, TAILLE_BLOC);
        memcpy(message_dechiffre + i, bloc, TAILLE_BLOC);

        memcpy(bloc_precedent, message_chiffre + i, TAILLE_BLOC);
    }
}

