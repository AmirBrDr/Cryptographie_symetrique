
import threading
import queue
import argparse

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
    with open(output_file, 'w') as f:
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
    with open(output_file, 'w') as f:
        f.write(f"Clé partagée (calculée par Bob) : {shared_key}\n")

# Lecture des paramètres depuis le fichier
def lire_parametres(fichier):
    with open(fichier, 'r') as f:
        lignes = f.readlines()
        p = int(lignes[0].strip())
        g = int(lignes[1].strip())
    return p, g

def main():
    # Gestion des arguments de la ligne de commande
    parser = argparse.ArgumentParser(description="Programme Diffie-Hellman")
    parser.add_argument('-i', '--input', required=True, help="Fichier d'entrée contenant les paramètres (p, g)")
    parser.add_argument('-o', '--output', required=True, help="Fichier de sortie pour la clé partagée")
    args = parser.parse_args()

    # Chargement des paramètres
    p, g = lire_parametres(args.input)

    # Création des queues pour la communication entre Alice et Bob
    param_queue = queue.Queue()
    alice_to_bob_queue = queue.Queue()
    bob_to_alice_queue = queue.Queue()

    # Ajout des paramètres dans la queue
    param_queue.put((p, g))

    # Démarrage des threads
    alice_thread = threading.Thread(target=alice, args=(param_queue, alice_to_bob_queue, bob_to_alice_queue, args.output))
    bob_thread = threading.Thread(target=bob, args=(param_queue, alice_to_bob_queue, bob_to_alice_queue, args.output))

    alice_thread.start()
    bob_thread.start()

    alice_thread.join()
    bob_thread.join()

if __name__ == "__main__":
    main()
