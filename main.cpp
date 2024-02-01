#include "Visiteur.h"
#include "Attraction.h"
#include <string>
#include <queue>
#include "Structure.hpp"
using namespace std;

int main() {
	// Utilisation de la classe Personne
	Visiteur visiteur1("Alice");
	visiteur1.AfficherDetails();
	Attraction attraction1("Toutatis", 20);
	attraction1.AfficherDetails();
	return 0;
}