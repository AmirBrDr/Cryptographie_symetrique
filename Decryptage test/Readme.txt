Ceci est le répertoire de test des fonctions break_code.

Notre problème majeur avec cette partie est que break_code_c1 n'émonde aucune clé, validant tout les caractères à chaque fois.
De plus nous n'avons pas réussis à implémenter la construction d'un tableau des clés possibles.

Chaque break_code de ce répertoire est indépendant, ils montrent ce pour quoi ils sont fonctionnels. Une partie du code a été retiré pour faciliter
la lecture. Les versions finales qui doivent fonctionner avec le main_break sont dans le répertoire source.

Break_code_c1 : prend en entrée : <taille_cle> <fichier_crypte> <fichier_log>
Il affiche dans le fichier de log les caractères validés, ligne pas ligne.

Break_code_c2 : prend en entree : <fichier_non_crypte>
Il affiche la fréquence de chaque caractère dans un fichier texte.

Break_code_c3 : prend en entrée : <fichier_non_crypte> <fichier_dictionnaire>
Il affiche le nombre de mots corrects dans un fichier texte selon la langue choisie.

Compilation :
gcc -Wall break_code_c1.c -o break_code_c1
gcc -Wall break_code_c2.c -o break_code_c2 -lm
gcc -Wall break_code_c3.c -o break_code_c3


long_texte.txt est un texte de mots aléatoires dont les accents ont été retirés.
long_texte_crypte.txt est le même fichier mais crypté avec la clé "taratata"