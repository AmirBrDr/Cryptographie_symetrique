#ifndef BREAK_CODE_C3_H
#define BREAK_CODE_C3_H

#include <stddef.h>

struct cle{
    char cle[62];
    float moy_freq_lettre;
    float mots_correctes;
};

/* Verifie si le mot est présent dans le dictionnaire
 * - `mot` : le mot à chercher
 * - `dico` : le dictionnaire
 */
bool mot_present(char *mot, char *dico);

/* Retourne le nombre de mots correctes avec un message déchiffré 
 * - `message_decrypte` : le message déchiffré
 * - `dico` : le dictionnaire
 * - `separators` : les séparateurs
*/
int nombre_mots_correctes(char *message_decrypte, char *dico, const char *separators);

#endif // BREAK_CODE_C3_H