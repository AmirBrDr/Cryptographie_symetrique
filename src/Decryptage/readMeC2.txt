long_texte.txt est un texte de mots aléatoires
long_texte_crypte.txt est le même fichier mais crypté avec la clé "taratata"


breakC1 :
Le programme doit prendre en paramètre la longueur de la clé à trouver, le fichier crypté et un fichier où écrire ses résutats.
Il doit retourner :
1- un fichier se sortie où il écris sur chaque ligne la liste des caractères possibles
2- un tableau de tableau contenant les caractères possibles

problème :
- Il valide chaque caractère (voir fichier de sortie)
- Il ne remplis pas le tableau correctement


breakC2 :
Le programme doit prendre en paramètre la longueur de la clé, le fichier crypté et le tableau retourné par breakC1
Il doit construire la liste de toutes les clés qui sont valides pour le fichier crypté.

exemple : 
clé à trouver cle = test

longueur clé = 4
caractères possibles = [[ab],  //caractères possibles pour cle[0]
                        [f],    //caractères possibles pour cle[1]
                        [gh],   //caractères possibles pour cle[2]
                        [xyz]]  //caractères possibles pour cle[3]

cle_possibles = ["afgx", "afgy", "afgz", "afhx", "afhy", "afhz",
                "bfgx", "bfgy", "bfgz", "bfhx", "bfhy", "bfhz"]

ensuite, il attribue chaque clé à une structure cle dans un tableau

structure cle composé :
-d'une chaine de caractère (la cle valide à tester)
-une distance de fréquence d'apparition des lettres (voir pdf)
-le nombre de mots valides (avec un dictionnaire)


pour chaque clé à tester, breakc2 decrypte le fichier avec xor et utilise la fonction moyenne_frequen_lettre pour lui donner sa distance
Plus elle est basse, plus la clé est probable.

Enfin le tableau des clé à tester est trié par ordre croissant, et on sélectionne les 20 premières pour les envoyer à break c3


Problèmes :
-je n'ai pas réussis à trouver un algorithme pour construire la liste des clés valides
-le programme réutilise mal la fonction xor (lorsqu'on essaye d'afficher le texte decrypté, seul le premier mot est decrytpé)
-j'ai du mal avec les paramètres de la fonction de tri (qui doit trier le tableau par ordre croissant de moyenne_frequen_lettre)
