#ifndef SYM_CRYPT_H
#define SYM_CRYPT_H

#include <stddef.h>

/* Fonction pour afficher l'aide et les options du programme */
void afficher_aide();

/* Fonction pour lire le contenu d'un fichier
 * - `nom_fichier` : nom du fichier à lire
 * - `contenu` : contenu du fichier
 * - `taille` : taille du fichier
 */
void lire_fichier(const char *nom_fichier, unsigned char **contenu, size_t *taille);

/* Fonction pour écrire le contenu dans un fichier
 * - `nom_fichier` : nom du fichier de sortie
 * - `contenu` : contenu à écrire
 * - `taille` : taille du contenu
 */
void ecrire_fichier(const char *nom_fichier, const unsigned char *contenu, size_t taille);

#endif // SYM_CRYPT_H