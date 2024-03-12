#include "main.h"
#include "Parc.h"
#include "Horloge.h"
#include "Attraction.h" // Inclure le fichier d'en-tête Attraction.h
#include "Visiteur.h" // Inclure le fichier d'en-tête Visiteur.h

int main() {
	// Création d'une instance de parc
	Parc monParc("Parc Astérix");

	// Création d'une instance d'attraction avec une longue file d'attente
	Attraction attraction("Toutatis", 20, 2);
	for (int i = 0; i < 500; ++i) { // Ajout de 500 visiteurs dans la file d'attente
		Visiteur* visiteur = new Visiteur("Visiteur " + std::to_string(i + 1)); // Créer un nouvel objet Visiteur sur le tas
		attraction.AjouterVisiteur(visiteur); // Passer le pointeur à la méthode AjouterVisiteur
	}

	// Ajout de l'attraction au parc
	monParc.AjouterAttraction(attraction);

	// Création d'une instance d'attraction avec une longue file d'attente
	Attraction attraction2("Discobélix", 50, 7);
	for (int i = 0; i < 500; ++i) { // Ajout de 500 visiteurs dans la file d'attente
		Visiteur* visiteur = new Visiteur("Visiteur " + std::to_string(i + 1)); // Créer un nouvel objet Visiteur sur le tas
		attraction2.AjouterVisiteur(visiteur); // Passer le pointeur à la méthode AjouterVisiteur
	}

	// Ajout de l'attraction au parc
	monParc.AjouterAttraction(attraction2);

	// Simulation de la journée dans le parc
	monParc.simulerJournee(10, 18);

	// Libérer la mémoire des visiteurs créés sur le tas
	for (Attraction& attraction : monParc.GetAttractions()) { // Utiliser une référence non constante ici
		std::queue<Visiteur*>& fileAttente = attraction.GetFileAttente();
		while (!fileAttente.empty()) {
			Visiteur* visiteur = fileAttente.front();
			delete visiteur; // Libérer la mémoire allouée pour chaque visiteur
			fileAttente.pop();
		}
	}

	return 0;
}