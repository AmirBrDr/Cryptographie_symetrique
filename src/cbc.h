#ifndef CBC_H
#define CBC_H

#include <stddef.h> // Pour le type size_t

#define TAILLE_BLOC 16

// Chiffrement par CBC
// cbc.h
void cbc_chiffrement(const unsigned char *message, size_t taille, const unsigned char *cle, const unsigned char *vi, unsigned char *message_chiffrer);
void cbc_dechiffrement(const unsigned char *message_chiffre, size_t taille, const unsigned char *cle, const unsigned char *vi, unsigned char *message_dechiffre);


#endif // CBC_H