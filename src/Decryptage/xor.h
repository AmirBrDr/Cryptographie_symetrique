#ifndef XOR_H
#define XOR_H

#include <stddef.h>

// Taille du bloc pour le chiffrement
#define TAILLE_BLOC 16

/* Fonction de chiffrement et déchiffrement XOR 
 * - `msg` : message à chiffrer
 * - `key` : clé de chiffrement
 * - `output` : message chiffré
 * - `msg_len` : longueur du message
 */
void xor_chiffre(const unsigned char *msg, const char *key, unsigned char *output, size_t msg_len, size_t key_len);

#endif // XOR_H