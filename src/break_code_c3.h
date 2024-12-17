#ifndef BREAK_CODE_C3_H
#define BREAK_CODE_C3_H

#include <stdbool.h>
#include <stddef.h>

#define maxCaractere 62

// Structure pour stocker une clé et ses statistiques
struct cle {
    char cle[maxCaractere];  // La clé elle-même
    float moy_freq_lettre;   // Moyenne des fréquences des lettres
    int mots_correctes;      // Nombre de mots corrects dans le texte décrypté
};

// Fonction pour lire un fichier
/// @brief Lit le contenu d'un fichier et stocke sa taille.
/// @param nom_fichier Le nom du fichier à lire.
/// @param contenu Pointeur pour stocker le contenu du fichier.
/// @param taille Pointeur pour stocker la taille du fichier.
void lire_fichier(const char *nom_fichier, unsigned char **contenu, size_t *taille);

// Fonction qui vérifie si un mot est présent dans le dictionnaire
/// @brief Vérifie si un mot donné existe dans le dictionnaire.
/// @param mot Le mot à vérifier.
/// @param dico Le contenu du dictionnaire.
/// @return Renvoie true si le mot est trouvé, sinon false.
bool mot_present(char *mot, char *dico);

// Fonction pour compter les mots corrects dans un message décrypté
/// @brief Compte le nombre de mots présents dans le dictionnaire.
/// @param message_decrypte Le message décrypté.
/// @param dico Le contenu du dictionnaire.
/// @param separators Les séparateurs utilisés pour diviser les mots.
/// @return Le nombre de mots corrects trouvés.
int nombre_mots_correctes(char *message_decrypte, char *dico, const char *separators);

#endif /* XOR_H */
