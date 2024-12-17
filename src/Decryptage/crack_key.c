#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEY_SIZE 10     // Taille maximale de la clé
#define MAX_CHARS 62        // Caractères alphanumériques valides
#define MSG_SIZE 1000       // Taille maximale du message

// Caractères alphanumériques valides
const char valid_chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

// Vérifier si un caractère déchiffré est valide (ASCII)
int is_valid_ascii(char c) {
    return (isalnum(c) || ispunct(c) || isspace(c));
}

// Valider une clé candidate en déchiffrant tout le message
int validate_key(const char *msg, int msg_len, const char *key, int key_size) {
    for (int i = 0; i < msg_len; i++) {
        char decoded = msg[i] ^ key[i % key_size];
        if (!is_valid_ascii(decoded)) {
            return 0; // La clé est invalide
        }
    }
    return 1; // La clé est valide
}

// Filtrer les candidats pour chaque position de la clé
void filter_candidates(const char *msg, int msg_len, char candidates[MAX_KEY_SIZE][MAX_CHARS], int key_size) {
    for (int i = 0; i < key_size; i++) {
        int valid_count = 0;
        char temp[MAX_CHARS] = {0};

        for (int c = 0; c < MAX_CHARS; c++) {
            int valid = 1;

            for (int j = i; j < msg_len; j += key_size) {
                char decoded = msg[j] ^ valid_chars[c];
                if (!is_valid_ascii(decoded)) {
                    valid = 0;
                    break;
                }
            }

            if (valid) {
                temp[valid_count++] = valid_chars[c];
            }
        }

        // Mise à jour des candidats pour la position courante
        memset(candidates[i], 0, MAX_CHARS);
        memcpy(candidates[i], temp, valid_count);
    }
}

// Générer et valider les clés candidates récursivement
void generate_valid_keys(FILE *output_file, const char *msg, int msg_len, char candidates[MAX_KEY_SIZE][MAX_CHARS],
                         int key_size, int depth, char *current_key) {
    if (depth == key_size) {
        current_key[depth] = '\0'; // Terminer la clé
        if (validate_key(msg, msg_len, current_key, key_size)) {
            fprintf(output_file, "%s\n", current_key); // Écrire la clé valide dans le fichier
        }
        return;
    }

    for (int i = 0; candidates[depth][i] != '\0'; i++) {
        current_key[depth] = candidates[depth][i];
        generate_valid_keys(output_file, msg, msg_len, candidates, key_size, depth + 1, current_key);
    }
}

int main() {
    char msg[MSG_SIZE];
    int key_size;
    char input_file_name[100], output_file_name[100];

    // Entrées utilisateur
    printf("Entrez le nom du fichier d'entrée : ");
    scanf("%s", input_file_name);
    printf("Entrez le nom du fichier de sortie : ");
    scanf("%s", output_file_name);
    printf("Entrez la taille de la clé : ");
    scanf("%d", &key_size);

    if (key_size <= 0 || key_size > MAX_KEY_SIZE) {
        printf("Taille de clé invalide.\n");
        return 1;
    }

    // Lecture du fichier d'entrée
    FILE *input_file = fopen(input_file_name, "r");
    if (!input_file) {
        printf("Erreur : impossible d'ouvrir le fichier d'entrée.\n");
        return 1;
    }
    int msg_len = fread(msg, sizeof(char), MSG_SIZE, input_file);
    fclose(input_file);

    printf("Message lu : %.*s\n", msg_len, msg);

    // Initialisation et filtrage des candidats
    char candidates[MAX_KEY_SIZE][MAX_CHARS] = {0};
    char current_key[MAX_KEY_SIZE + 1] = {0};

    for (int i = 0; i < key_size; i++) {
        strcpy(candidates[i], valid_chars);
    }

    filter_candidates(msg, msg_len, candidates, key_size);

    // Génération et écriture des clés valides
    FILE *output_file = fopen(output_file_name, "w");
    if (!output_file) {
        printf("Erreur : impossible d'ouvrir le fichier de sortie.\n");
        return 1;
    }
    generate_valid_keys(output_file, msg, msg_len, candidates, key_size, 0, current_key);
    fclose(output_file);

    printf("Les clés valides ont été écrites dans le fichier : %s\n", output_file_name);
    return 0;
}
