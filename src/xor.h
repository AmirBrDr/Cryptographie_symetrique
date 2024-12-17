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

/* Fonction de génération aléatoire d'une clé alphanumérique 
 * - `key` : clé générée
 * - `key_len` : longueur de la clé
*/
void gen_key(unsigned char *key, size_t key_len);

/* Fonction pour sauvegarder la clé dans un fichier 
 * - `filename` : nom du fichier
 * - `key` : clé à sauvegarder
 */
void save_key_to_file(const char *filename, const unsigned char *key);

#endif // XOR_H