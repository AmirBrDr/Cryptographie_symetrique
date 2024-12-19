#ifndef BREAK_CODE_C2_TEST_H
#define BREAK_CODE_C2_TEST_H

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
void tri_croissant(struct cle tab_cle[], int taille);

#endif // BREAK_CODE_C2_TEST_H