#include "Visiteur.h"
#include "Attraction.h"
#include <string>
#include <queue>
#include "Structure.hpp"
#include "Horloge.h"
#include <thread>
using namespace std;

#include <iostream>
#include "Horloge.h" // Inclure le fichier d'en-tête de la classe Horloge


void avancerTemps(Horloge& horloge) {
	// Durée entre chaque avancement du temps (10 secondes dans cet exemple)
	std::chrono::seconds dureeAvancement(10);

	while (true) {
		// Avancer le temps de 1 heure
		horloge.avancerTemps(1);

		// Afficher l'heure actuelle
		std::cout << "Heure actuelle : " << horloge.getHeureActuelle() << "h" << std::endl;

		// Attendre la durée d'avancement
		std::this_thread::sleep_for(dureeAvancement);

		// Sortir de la boucle si l'heure actuelle est 23h
		if (horloge.getHeureActuelle() == 23) {
			break;
		}
	}
}

int main() {
	Horloge horloge;

	// Créer un thread pour faire avancer le temps
	std::thread threadAvancement(avancerTemps, std::ref(horloge));

	// Attendre que le thread de l'avancement du temps se termine
	threadAvancement.join();

	return 0;
}