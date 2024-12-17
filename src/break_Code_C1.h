#ifndef BREAK_CODE_C1_H
#define BREAK_CODE_C1_H

#include <stdbool.h>
#include <stddef.h>

// Déclaration des variables globales
extern char *alphabet; // Alphabet utilisé pour vérifier les caractères valides
extern int maxCaracteres; // Nombre total de caractères dans l'alphabet
extern int tailleClef; // Taille de la clé

/// @brief Vérifie si un caractère est valide en appliquant un XOR avec le message d'entrée.
/// @param message_entree Le message d'entrée (fichier ou texte à décoder).
/// @param caractere Le caractère à vérifier.
/// @param tailleClef La longueur de la clé utilisée pour décoder.
/// @param indiceClef L'index dans la clé utilisé pour le décodage.
/// @param taille_fichier La taille du fichier (ou du texte) à décoder.
/// @return Retourne vrai si le caractère XORé est alphanumérique ou un espace, sinon retourne faux.
bool charCorrect(const char *message_entree, char caractere, int tailleClef, int indiceClef, int taille_fichier);

/// @brief Fonction pour générer les clés possibles en se basant sur le texte chiffré.
/// @param message_entree Le message chiffré (texte à décoder).
/// @param taille_cle La taille de la clé utilisée pour le décryptage.
/// @param cle_possibles Tableau à remplir avec les clés possibles.
/// @param nombre_cle Nombre total de clés possibles à générer.
void break_Code_C1(const unsigned char *message_entree, size_t taille_cle, char cle_possibles[][maxCaracteres], int *nombre_cle);

S
#endif /* BREAK_CODE_C1_H */
