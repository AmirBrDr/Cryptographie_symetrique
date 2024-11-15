import threading
import queue
import sys

# Fonction de puissance modulaire
def puissance_mod_n(a: int, e: int, n: int) -> int:
    p = 1
    while e > 0:
        if e % 2 != 0:
            p = (p * a) % n
        a = (a * a) % n
        e //= 2
    return p

# Fonction pour Alice
def alice(param_queue, alice_to_bob_queue, bob_to_alice_queue, output_file):
    p, g = param_queue.get()
    a = 6  # Choisir un secret pour Alice
    A = puissance_mod_n(g, a, p)  # Calculer A = g^a mod p
    print(f"Alice envoie A = {A} à Bob.")
    alice_to_bob_queue.put(A)  # Envoi de A à Bob

    # Attendre la réception de B
    B = bob_to_alice_queue.get()
    shared_key = puissance_mod_n(B, a, p)
    print(f"Alice calcule la clé partagée = {shared_key}")

    # Enregistrement de la clé partagée dans le fichier de sortie
    with open(output_file, 'a') as f:
        f.write(f"Clé partagée (calculée par Alice) : {shared_key}\n")

# Fonction pour Bob
def bob(param_queue, alice_to_bob_queue, bob_to_alice_queue, output_file):
    p, g = param_queue.get()
    b = 15  # Choisir un secret pour Bob
    B = puissance_mod_n(g, b, p)  # Calculer B = g^b mod p
    print(f"Bob envoie B = {B} à Alice.")
    bob_to_alice_queue.put(B)  # Envoi de B à Alice

    # Attendre la réception de A
    A = alice_to_bob_queue.get()
    shared_key = puissance_mod_n(A, b, p)
    print(f"Bob calcule la clé partagée = {shared_key}")

    # Enregistrement de la clé partagée dans le fichier de sortie
    with open(output_file, 'a') as f:
        f.write(f"Clé partagée (calculée par Bob) : {shared_key}\n")

def print_usage():
    print("Usage: script.py -i input_file -o output_file [-h]")
    print("Options:")
    print("  -i input_file   Spécifie le fichier d'entrée.")
    print("  -o output_file  Spécifie le fichier de sortie.")
    print("  -h              Affiche ce message d'aide.")

# Fonction principale pour gérer les paramètres et lancer les threads
def main():
    input_file = None
    output_file = None

    # Parcours des arguments de la ligne de commande
    for i in range(1, len(sys.argv)):
        if sys.argv[i] == "-i" and (i + 1) < len(sys.argv):
            input_file = sys.argv[i + 1]
            i += 1  # Passer l'argument du fichier
        elif sys.argv[i] == "-o" and (i + 1) < len(sys.argv):
            output_file = sys.argv[i + 1]
            i += 1  # Passer l'argument du fichier
        elif sys.argv[i] == "-h":
            print_usage()
            sys.exit(0)

    # Vérification des arguments obligatoires
    if not input_file or not output_file:
        print("Erreur : Les arguments -i et -o sont obligatoires.")
        print_usage()
        sys.exit(1)

    with open(input_file, 'r') as f:
        lines = f.readlines()
        p = int(lines[0].split('=')[1].strip())
        g = int(lines[1].split('=')[1].strip())

    # Configuration des files de messages pour la communication entre Alice et Bob
    param_queue = queue.Queue()
    alice_to_bob_queue = queue.Queue()
    bob_to_alice_queue = queue.Queue()

    # Pousse les paramètres dans la file d'attente
    param_queue.put((p, g))
    param_queue.put((p, g))

    # État initial pour Eve (l'espionne)
    print(f"Eve (l'espionne) connaît : p = {p}, g = {g}")

    # Création et démarrage des threads pour Alice et Bob
    alice_thread = threading.Thread(target=alice, args=(param_queue, alice_to_bob_queue, bob_to_alice_queue, output_file))
    bob_thread = threading.Thread(target=bob, args=(param_queue, alice_to_bob_queue, bob_to_alice_queue, output_file))

    alice_thread.start()
    bob_thread.start()

    # Attendre que les deux threads se terminent
    alice_thread.join()
    bob_thread.join()
    print("Échange de clés terminé, clé partagée enregistrée dans le fichier de sortie.")

main()