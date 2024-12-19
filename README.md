# Cryptographie_symetrique
Projet Avancé Équipe 6:

CARCY Axel
URIBE Ivan
GHASEMI Amirmahdi
MAATI Mohammed


-------------------------------------------Compilation des mains:-------------------------------------------------------------------------------

gcc Wall symcrypt.c -o symcrypt

Utilisation : symcrypt -i <fichier_entree> -o <fichier_sortie> -k <cle> | -f <fichier_cle> -m <methode> -v <fichier_iv> [-l <fichier_log>]

Options :
            "  -i <fichier_entree>   Fichier contenant le texte en clair (obligatoire)
            "  -o <fichier_sortie>   Fichier de sortie pour le texte chiffré (obligatoire)
            "  -k <cle>              Clé pour le chiffrement/déchiffrement (obligatoire)
            "  -f <fichier_cle>      Fichier contenant la clé (alternative à -k)
            "  -m <methode>          Méthode (xor, cbc-crypt, cbc-uncrypt, masque)
            "  -v <fichier_iv>       Fichier du vecteur d'initialisation (obligatoire pour CBC)
            "  -l <fichier_log>      Fichier de log (optionnel, par défaut stderr)
            "  -h                    Afficher ce message d'aide


gcc Wall break_code_main.c -o break_code_main

Utilisation : break_code -i <fichier_entree> -m <methode> -k <longueur_cle> [-d <fichier_dictionnaire>] [-l <fichier_log>] -lm

Options :
            "  -i <fichier_entree>   Fichier contenant le texte crypté (obligatoire)
            "  -m <methode>          Méthode (c1, all)
            "  -k <cle>              Longueur de la clé ayant servie à crypter le texte (obligatoire)
            "  -d <fichier_cle>      Fichier contenant le dictionnaire (obligatoire si all)
            "  -l <fichier_log>      Fichier de log (optionnel, par défaut stderr)
            "  -h                    Afficher ce message d'aide
