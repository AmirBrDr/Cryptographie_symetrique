#ifndef CBC_H
#define CBC_H

#include <stddef.h> // Para el tipo size_t

#define TAILLE_BLOC 16

// Función para cifrar usando el modo CBC
void cbc_chiffrement(const unsigned char *message, const unsigned char *cle, const unsigned char *vi, unsigned char *message_chiffrer);

// Función para descifrar usando el modo CBC
void cbc_dechiffrement(unsigned char *message_chiffre, unsigned char *cle, unsigned char *vi, unsigned char *message_dechiffre);

// Función para realizar la operación XOR
void xor_chiffre(const unsigned char *msg, const unsigned char *key, unsigned char *output, size_t msg_len);

#endif // CBC_H