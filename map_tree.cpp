#include <cstdlib>
#include <iostream>
#include <map>

int main() {
  std::map<int, int> arbre;
  int choix, val;

  while (true) {
    std::cout << "\n1. Inserer\n2. Afficher\n3. Inserer 1M valeurs aleatoires\n0. Quitter\nChoix: ";
    if (!(std::cin >> choix)) return 0;

    switch (choix) {
    case 1:
      std::cout << "Valeur: ";
      if (!(std::cin >> val)) return 0;
      arbre[val]++;
      break;
    case 2:
      for (const auto &element : arbre)
        for (int i = 0; i < element.second; i++)
          std::cout << element.first << ' ';
      std::cout << '\n';
      break;
    case 3:
      for (int i = 0; i < 1000000; i++)
        arbre[std::rand() % 1000000]++;
      std::cout << "1000000 valeurs inserees\n";
      break;
    case 0:
      return 0;
    default:
      std::cout << "Choix invalide\n";
    }
  }
}
