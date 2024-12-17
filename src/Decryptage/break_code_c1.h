#ifndef BREAK_CODE_C1_H
#define BREAK_CODE_C1_H

#include <stddef.h>

/* Determine si un caractère decrypte correctement tout le fichier 
 * - `message_entree` : message chiffré
 * - `caractere` : caractère à tester
 * - `tailleClef` : taille de la clé
 * - `indiceClef` : indice de la clé
 * - `taille_fichier` : taille du fichier
 */
bool charCorrect(const char *message_entree, char caractere, int tailleClef, int indiceClef, int taille_fichier);

/* Fonction pour casser le code C1
 * - `message_entree` : message chiffré
 * - `taille_cle` : taille de la clé
 * - `cle_possibles` : clés possibles
 * - `nombre_cle` : nombre de clés possibles
 */
void break_code_c1(const unsigned char *message_entree, size_t taille_cle, char **cle_possibles, int *nombre_cle);

#endif // BREAK_CODE_C1_H