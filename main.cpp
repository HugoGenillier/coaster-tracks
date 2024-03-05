#include "main.h"
#include "Parc.h"
#include "Horloge.h"

int main() {
	// Cr�ation d'une instance de parc
	Parc monParc("Parc Ast�rix");

	// Cr�ation d'une instance d'attraction avec une longue file d'attente
	Attraction attraction("Toutatis", 20, 2);
	for (int i = 0; i < 500; ++i) { // Ajout de 500 visiteurs dans la file d'attente
		Visiteur visiteur("Visiteur " + std::to_string(i + 1));
		attraction.AjouterVisiteur(visiteur);
	}

	// Ajout de l'attraction au parc
	monParc.AjouterAttraction(attraction);

	// Cr�ation d'une instance d'attraction avec une longue file d'attente
	Attraction attraction2("Discob�lix", 50, 7);
	for (int i = 0; i < 500; ++i) { // Ajout de 500 visiteurs dans la file d'attente
		Visiteur visiteur("Visiteur " + std::to_string(i + 1));
		attraction2.AjouterVisiteur(visiteur);
	}

	// Ajout de l'attraction au parc
	monParc.AjouterAttraction(attraction2);

	// Simulation de la journ�e dans le parc
	monParc.simulerJournee(10, 18);

	return 0;
}