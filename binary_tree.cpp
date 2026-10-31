#include <cstdlib>
#include <iostream>

class Noeud {
public:
  int valeur;
  Noeud *fd;
  Noeud *fg;

  Noeud(int v) {
    valeur = v;
    fd = nullptr;
    fg = nullptr;
  }
};

class ArbreBin {
public:
  Noeud *racine = nullptr;

  Noeud *inserer(Noeud *courant, int val) {
    if (!courant) {
      return new Noeud(val);
    }
    if (val <= courant->valeur) {
      courant->fg = inserer(courant->fg, val);
    } else if (val > courant->valeur) {
      courant->fd = inserer(courant->fd, val);
    }
    return courant;
  }

  void afficher(Noeud *courant) {
    if (courant) {
      afficher(courant->fg);
      std::cout << courant->valeur << " ";
      afficher(courant->fd);
    }
  }

  void detruire(Noeud *courant) {
    if (courant) {
      detruire(courant->fg);
      detruire(courant->fd);
      delete courant;
    }
  }

  ~ArbreBin() { detruire(racine); }

  ArbreBin() = default;
  ArbreBin(const ArbreBin &) = delete;
  ArbreBin &operator=(const ArbreBin &) = delete;
};

int main() {
  ArbreBin arbre;
  int choix;
  int val;

  while (true) {
    std::cout << "\n1. Inserer\n"
              << "2. Afficher\n"
              << "3. Inserer 1M valeurs aleatoires\n"
              << "0. Quitter\n"
              << "Choix: ";
    std::cin >> choix;

    switch (choix) {
    case 1:
      std::cout << "Valeur: ";
      std::cin >> val;
      arbre.racine = arbre.inserer(arbre.racine, val);
      break;
    case 2:
      std::cout << "\n";
      arbre.afficher(arbre.racine);
      std::cout << "\n";
      break;
    case 3:
      for (int i = 0; i < 1000000; i++) {
        arbre.racine = arbre.inserer(arbre.racine, std::rand() % 1000000);
      }
      std::cout << "1000000 valeurs inserees\n";
      break;
    case 0:
      return 0;
    default:
      std::cout << "Choix invalide\n";
      break;
    }
  }
}
