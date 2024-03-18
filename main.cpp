#include "Parc.h"
#include "Attraction.h"
#include "Visiteur.h"
#include "Horloge.h"

int main() {
	// Création d'une instance de parc
	Parc monParc("Parc d'attractions");

	// Création d'attractions avec des files d'attente et des positions
	Attraction toutatis("Toutatis", 20, 2, { 300, 0 });
	Attraction discobelix("Discobelix", 50, 7, { 0, 400 });

	// Ajouter des attractions au parc
	monParc.AjouterAttraction(toutatis);
	monParc.AjouterAttraction(discobelix);

	// Création de visiteurs
	std::vector<Visiteur> visiteurs;
	std::vector<Attraction>& attractions = monParc.GetAttractions(); // Obtenir le vecteur d'attractions
	for (int i = 0; i < 100; ++i) {
		std::string nomVisiteur = "Visiteur " + std::to_string(i + 1);
		Visiteur visiteur(nomVisiteur, attractions); // Passer le vecteur d'attractions au constructeur du visiteur
		visiteurs.push_back(visiteur);
		monParc.AjouterVisiteur(visiteur); // Ajouter le visiteur au vecteur de visiteurs du parc
	}

	// Simulation de la journée
	monParc.simulerJournee(10, 18);

	// Libération de la mémoire des visiteurs
	monParc.LibérerVisiteurs();

	return 0;
}