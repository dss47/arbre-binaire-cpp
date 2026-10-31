#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <vector>

#define main programme_arbre_main
#include "binary_tree.cpp"
#undef main

template <typename F> double chrono_ms(F fonction) {
  auto debut = std::chrono::steady_clock::now();
  fonction();
  auto fin = std::chrono::steady_clock::now();
  return std::chrono::duration<double, std::milli>(fin - debut).count();
}

bool rechercher(Noeud *courant, int valeur) {
  while (courant) {
    if (courant->valeur == valeur) return true;
    if (valeur < courant->valeur) courant = courant->fg;
    else courant = courant->fd;
  }
  return false;
}

void comparer(const std::vector<int> &valeurs,
              const std::vector<int> &requetes) {
  ArbreBin arbre;
  std::map<int, int> map;
  int trouvesArbre = 0;
  int trouvesMap = 0;

  double ajoutArbre = chrono_ms([&] {
    for (int valeur : valeurs)
      arbre.racine = arbre.inserer(arbre.racine, valeur);
  });

  double ajoutMap = chrono_ms([&] {
    for (int valeur : valeurs) map[valeur]++;
  });

  double rechercheArbre = chrono_ms([&] {
    for (int valeur : requetes)
      trouvesArbre += rechercher(arbre.racine, valeur);
  });

  double rechercheMap = chrono_ms([&] {
    for (int valeur : requetes)
      trouvesMap += map.find(valeur) != map.end();
  });

  std::cout << std::setw(10) << valeurs.size() << std::setw(20) << ajoutArbre
            << std::setw(18) << ajoutMap << std::setw(20) << rechercheArbre
            << std::setw(18) << rechercheMap << '\n';

  if (trouvesArbre != trouvesMap)
    std::cout << "Erreur: les recherches donnent des resultats differents\n";
}

int main() {
  std::mt19937 generateur(42);
  const int nombreRecherches = 10000;

  std::cout << std::fixed << std::setprecision(3);
  std::cout << "Temps en ms, " << nombreRecherches
            << " recherches par test\n";
  std::cout << std::setw(10) << "N" << std::setw(20) << "ajout arbre"
            << std::setw(18) << "ajout map" << std::setw(20)
            << "recherche arbre" << std::setw(18) << "recherche map"
            << '\n';

  for (int n : {1000, 10000, 100000, 1000000}) {
    std::uniform_int_distribution<int> distribution(0, 2 * n);
    std::vector<int> valeurs(n);
    std::vector<int> requetes(nombreRecherches);

    for (int &valeur : valeurs) valeur = distribution(generateur);
    for (int &valeur : requetes) valeur = distribution(generateur);

    comparer(valeurs, requetes);
  }
}
