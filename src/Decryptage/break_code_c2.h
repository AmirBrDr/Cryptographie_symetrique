#ifndef BREAK_CODE_C2_H
#define BREAK_CODE_C2_H

#include <stddef.h>

/* Fonction qui calcule la distance entre les fréquences attendues et observées
 * - `message` : le message à analyser
 * - `taille` : la taille du message
 */
float moyenne_frequence_lettre(const unsigned char *message, size_t taille);

/* Tri par ordre croissant 
 * - `tab_cle` : tableau de clés à trier
 * - `taille` : taille du tableau
 */
void tri_croissant(struct cle *tab_cle, int taille);

/* Fonction pour casser le code C2
 * - `message_entree` : le message chiffré
 * - `taille_cle` : la taille de la clé
 * - `taille_message` : la taille du message
 * - `cle_possibles` : les clés possibles
 * - `tab_cle_probables` : tableau des clés probables
 * - `total_cle` : le nombre total de clés
 */
void break_code_c2(const unsigned char *message_entree, size_t taille_cle, size_t taille_message, char **cle_possibles, struct cle *tab_cle_probables, int total_cle);

#endif // BREAK_CODE_C2_H