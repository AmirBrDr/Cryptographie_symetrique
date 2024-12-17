#ifndef BREAK_CODE_C2_H
#define BREAK_CODE_C2_H

#include <stdbool.h>
#include <stddef.h>

#define maxCaractere 62

// Structure pour stocker une clé et ses statistiques
struct cle {
    char cle[maxCaractere];         // La clé elle-même
    float moy_freq_lettre;          // Moyenne des fréquences des lettres
    float mots_correctes;           // Nombre de mots corrects (non utilisé dans ce code)
};

// Déclaration des statistiques de fréquences des lettres en français
extern float stat_thFr[26];

// Déclaration des statistiques de fréquences des lettres en anglais
extern float stat_thEn[26];

// Alphabet utilisé pour les opérations
extern char *alphabet;

// Fonction de chiffrement et déchiffrement XOR
/// @brief Applique un XOR entre le message et la clé pour chiffrer/déchiffrer.
/// @param msg Le message à chiffrer ou déchiffrer.
/// @param key La clé utilisée pour l'opération XOR.
/// @param output Le résultat du chiffrement/déchiffrement.
/// @param msg_len La longueur du message.
void xor_chiffre(const unsigned char *msg, const unsigned char *key, unsigned char *output, size_t msg_len);

// Fonction pour lire un fichier
/// @brief Lit le contenu d'un fichier et stocke sa taille.
/// @param nom_fichier Le nom du fichier à lire.
/// @param contenu Pointeur pour stocker le contenu du fichier.
/// @param taille Pointeur pour stocker la taille du fichier.
void lire_fichier(const char *nom_fichier, unsigned char **contenu, size_t *taille);

// Fonction qui calcule la distance entre la fréquence des lettres attendue et celle du fichier décrypté
/// @brief Calcule la moyenne des écarts des fréquences des lettres entre le message décrypté et la langue.
/// @param message_decrypte Le message décrypté.
/// @return La moyenne des écarts.
float moyenne_frequence_lettre(char *message_decrypte);

// Fonction qui trie les clés par ordre croissant en fonction de la moyenne des fréquences des lettres
/// @brief Trie un tableau de structures de clés par ordre croissant de moyennes des fréquences.
/// @param tab_cle Tableau de structures de clés.
void tri_croissant(struct cle *tab_cle[]);

#endif /* BREAK_CODE_C2_H */
