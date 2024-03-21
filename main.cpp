#include "Parc.h"
#include "Attraction.h"
#include "Visiteur.h"
#include "Horloge.h"

int main() {
	// Création d'une instance de parc
	Parc monParc("Parc Astérix");

	// Création d'attractions avec des caractéristiques et des positions
	Attraction toutatis("Toutatis", 20, 2, { 25, 10 });
	monParc.AjouterAttraction(toutatis);

	Attraction discobelix("Discobelix", 40, 5, { 0, 17 });
	monParc.AjouterAttraction(discobelix);

	Attraction goudurix("Goudurix", 20, 3, { 9,11 });
	monParc.AjouterAttraction(goudurix);

	Attraction traceDuHourra("La trace du Hourra", 20, 3, { -9,11 });
	monParc.AjouterAttraction(traceDuHourra);

	Attraction oziris("Oz'iris", 20, 3, { -18,5 });
	monParc.AjouterAttraction(traceDuHourra);

	// Création de visiteurs
	std::vector<Visiteur> visiteurs;
	std::vector<Attraction>& attractions = monParc.GetAttractions(); // Obtenir le vecteur d'attractions
	for (int i = 0; i < 500; ++i) {
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