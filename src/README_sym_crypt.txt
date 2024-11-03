# Equipe 6 
Amirmahdi GHASEMI, Ivan URIB, Axel CARCY, Mohamed-Yâ-Sîn MAATI

# README pour le programme sym_crypt

## Introduction
sym_crypt est un programme de chiffrement et de déchiffrement symétrique qui permet d’appliquer plusieurs méthodes de cryptographie, notamment le XOR, le masque et le mode CBC. Il prend en charge l'utilisation de fichiers pour l'entrée et la sortie, et propose la gestion de fichiers de clé et de vecteur d'initialisation (IV).

## Utilisation
Le programme s'utilise en ligne de commande avec la syntaxe suivante :


sym_crypt -i <fichier_entree> -o <fichier_sortie> -k <cle> | -f <fichier_cle> -m <methode> -v <fichier_iv> [-l <fichier_log>]


### Options
- -i <fichier_entree> : Fichier contenant le texte en clair (obligatoire).
- -o <fichier_sortie> : Fichier de sortie pour le texte chiffré/déchiffré (obligatoire).
- -k <cle> : Clé de chiffrement/déchiffrement (obligatoire, sauf si `-f` est utilisé).
- -f <fichier_cle> : Fichier contenant la clé (alternative à l'option `-k`).
- -m <methode> : Méthode de chiffrement/déchiffrement, parmi :
  - xor : Utilise le chiffrement XOR.
  - cbc-crypt : Utilise le mode CBC pour le chiffrement.
  - mask : Applique un masque pour le chiffrement.
- -v <fichier_iv> : Fichier contenant le vecteur d'initialisation (utilisé uniquement pour cbc-crypt).
- -l <fichier_log> : Fichier de log (optionnel). Si non spécifié, la sortie est redirigée vers stderr.

## Exemples d’utilisation

### 1. Chiffrement en mode CBC

sym_crypt -i clair.txt -o crypt.txt -k taratata -m cbc-crypt -v iv.txt


### 2. Déchiffrement en mode XOR avec un fichier de log

sym_crypt -o clair.txt -i crypt.txt -f key.txt -m xor -l log.txt


### 3. Chiffrement par masque

sym_crypt -i clair.txt -o crypt.txt -f key.txt -m mask


## Remarques
- Le programme inclut une gestion des erreurs, affichant des messages explicatifs en cas de problème avec les fichiers ou des options manquantes.
- Pour afficher l'aide rapidement, utilisez la commande suivante :

sym_crypt -h
