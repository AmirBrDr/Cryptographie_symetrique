# Equipe 6 
Amirmahdi GHASEMI, Ivan URIB, Axel CARCY, Mohamed-Yâ-Sîn MAATI

Échange de Diffie-Hellman 

Cette partie contient deux outils pour générer des paramètres Diffie-Hellman et des clés. 

Contenu des fichiers
- dh_gen_group.c : Programme pour générer les paramètres de groupe Diffie-Hellman(p et g).
- dh_genkey.py : Script Python pour générer une clé Diffie-Hellman à partir des paramètres et simuler l'échange de la clé secrète entre Alice et Bob.

---

Compilation et utilisation

Étape 1 : Génération des paramètres Diffie-Hellman
1. Compilez le programme en C :
   gcc dh_gen_group.c dh_prime.c -o dh_gen_group
2. Exécutez le programme pour générer un fichier contenant les paramètres :
   ./dh_gen_group -o param.txt
   - -o param.txt : Spécifie le fichier de sortie pour enregistrer les paramètres.

Étape 2 : Génération d'une clé Diffie-Hellman
1. Exécutez le script pour générer une clé :
   python3 dh_genkey.py -i param.txt -o key.txt
   - -i param.txt : Spécifie le fichier d'entrée contenant les paramètres.
   - -o key.txt : Spécifie le fichier de sortie pour enregistrer la clé secrète générée.

---

Exemple d'utilisation complet
1. Génération des paramètres :
   ./dh_gen_group -o param.txt
2. Génération de la clé :
   python3 dh_genkey.py -i param.txt -o key.txt

---

Dépendances
- dh_gen_group.c : Nécessite un compilateur C (par exemple, GCC).
- dh_genkey.py : Nécessite Python 3 et les modules standard.
