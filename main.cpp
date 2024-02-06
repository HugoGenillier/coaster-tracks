#include "Visiteur.h"
#include "Attraction.h"
#include <string>
#include <queue>
#include "Structure.hpp"
#include "Horloge.h"
using namespace std;

#include <iostream>
#include "Horloge.h" // Inclure le fichier d'en-tête de la classe Horloge

int main() {
	Horloge horloge; // Créer une instance de la classe Horloge

	std::cout << "Heure actuelle : " << horloge.getHeureActuelle() << "h" << std::endl;

	// Avancer le temps de 8 heures
	horloge.avancerTemps(8);

	std::cout << "Heure actuelle : " << horloge.getHeureActuelle() << "h" << std::endl;

	// Avancer le temps de 18 heures
	horloge.avancerTemps(18);

	std::cout << "Heure actuelle : " << horloge.getHeureActuelle() << "h" << std::endl;

	return 0;
}