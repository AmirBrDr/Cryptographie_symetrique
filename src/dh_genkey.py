import threading
import queue
import sys

# Fonction de puissance modulaire
def puissance_mod_n(a: int, e: int, n: int) -> int:
    result = 1
    a = a % n
    while e > 0:
        if (e % 2) == 1:  # Si e est impair
            result = (result * a) % n
        e = e >> 1  # Division par 2
        a = (a * a) % n  # a^2
    return result

def alice(param_queue):
    p, g = param_queue.get()
    a = 6  # Choisir un secret pour Alice
    A = puissance_mod_n(g, a, p)  # Calculer A = g^a [p]
    print(f"Alice envoie A = {A} à Bob.")
    return A, a

def bob(param_queue):
    p, g = param_queue.get()
    b = 15  # Choisir un secret pour Bob
    B = puissance_mod_n(g, b, p)  # Calculer B = g^b [p]
    print(f"Bob envoie B = {B} à Alice.")
    return B, b

def main(input_file):
    with open(input_file, 'r') as f:
        lines = f.readlines()
        p = int(lines[0].split('=')[1].strip())
        g = int(lines[1].split('=')[1].strip())

    param_queue = queue.Queue()
    param_queue.put((p, g))

    # Threads pour Alice et Bob
    a_thread = threading.Thread(target=alice, args=(param_queue,))
    b_thread = threading.Thread(target=bob, args=(param_queue,))

    a_thread.start()
    b_thread.start()

    a_thread.join()
    b_thread.join()

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 dh_genkey.py -i <input_file>")
        sys.exit(1)

    input_file = sys.argv[2]
    main(input_file)
