#include "main.h"
#include "Parc.h"
#include "Horloge.h"
#include "Attraction.h" // Inclure le fichier d'en-t�te Attraction.h
#include "Visiteur.h" // Inclure le fichier d'en-t�te Visiteur.h

int main() {
	// Cr�ation d'une instance de parc
	Parc monParc("Parc Ast�rix");

	// Cr�ation d'une instance d'attraction avec une longue file d'attente
	Attraction attraction("Toutatis", 20, 2);
	for (int i = 0; i < 500; ++i) { // Ajout de 500 visiteurs dans la file d'attente
		Visiteur* visiteur = new Visiteur("Visiteur " + std::to_string(i + 1)); // Cr�er un nouvel objet Visiteur sur le tas
		attraction.AjouterVisiteur(visiteur); // Passer le pointeur � la m�thode AjouterVisiteur
	}

	// Ajout de l'attraction au parc
	monParc.AjouterAttraction(attraction);

	// Cr�ation d'une instance d'attraction avec une longue file d'attente
	Attraction attraction2("Discob�lix", 50, 7);
	for (int i = 0; i < 500; ++i) { // Ajout de 500 visiteurs dans la file d'attente
		Visiteur* visiteur = new Visiteur("Visiteur " + std::to_string(i + 1)); // Cr�er un nouvel objet Visiteur sur le tas
		attraction2.AjouterVisiteur(visiteur); // Passer le pointeur � la m�thode AjouterVisiteur
	}

	// Ajout de l'attraction au parc
	monParc.AjouterAttraction(attraction2);

	// Simulation de la journ�e dans le parc
	monParc.simulerJournee(10, 18);

	// Lib�rer la m�moire des visiteurs cr��s sur le tas
	for (Attraction& attraction : monParc.GetAttractions()) { // Utiliser une r�f�rence non constante ici
		std::queue<Visiteur*>& fileAttente = attraction.GetFileAttente();
		while (!fileAttente.empty()) {
			Visiteur* visiteur = fileAttente.front();
			delete visiteur; // Lib�rer la m�moire allou�e pour chaque visiteur
			fileAttente.pop();
		}
	}

	return 0;
}