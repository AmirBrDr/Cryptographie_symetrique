#include <stdio.h>
#include <string.h>

void xor_chiffre(const unsigned char *msg, const unsigned char *key, unsigned char *output, size_t msg_len, int key_size) {
    for (size_t i = 0; i < msg_len; i++) {
        output[i] = msg[i] ^ key[i % key_size];
    }
}

int main() {
    const char *message = "Ceci est un message secret!";
    const char *key = "a1x";
    unsigned char output[100];

    xor_chiffre((unsigned char *)message, (unsigned char *)key, output, strlen(message), strlen(key));

    FILE *f = fopen("long_texte.txt", "wb");
    fwrite(output, 1, strlen(message), f);
    fclose(f);

    printf("Message chiffré écrit dans 'long_texte.txt'\n");
    return 0;
}
