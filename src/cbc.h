#ifndef CBC_H
#define CBC_H

#include <stddef.h> // Pour le type size_t

#define TAILLE_BLOC 16


/* 
 * Fonction de chiffrement CBC (Cipher Block Chaining) 
 * Cette fonction chiffre le message en utilisant le mode CBC. 
 * Elle prend en paramètre :
 * - `message`: les données binaires à chiffrer
 * - `message_len`: la longueur des données
 * - `cle`: la clé de chiffrement
 * - `vi`: le vecteur d'initialisation (IV)
 * - `message_chiffrer`: le tampon où sera stocké le message chiffré
 */
void cbc_chiffrement(const unsigned char *message, size_t taille, const unsigned char *cle, const unsigned char *vi, unsigned char *message_chiffrer);


/* Fonction de déchiffrement CBC (Cipher Block Chaining)
 * Cette fonction déchiffre un message chiffré en mode CBC.
 * Elle prend en paramètre :
 * - `message_chiffre`: les données chiffrées
 * - `message_len`: la longueur des données chiffrées
 * - `cle`: la clé de déchiffrement
 * - `vi`: le vecteur d'initialisation (IV)
 * - `message_dechiffre`: le tampon où sera stocké le message déchiffré
*/
void cbc_dechiffrement(const unsigned char *message_chiffre, size_t taille, const unsigned char *cle, const unsigned char *vi, unsigned char *message_dechiffre);


#endif // CBC_H