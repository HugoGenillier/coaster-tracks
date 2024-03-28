#include "Parc.h"
#include "Attraction.h"
#include "Visiteur.h"
#include "Horloge.h"

int main() {
	// Créer une fenêtre SFML
	sf::RenderWindow window(sf::VideoMode(800, 600), "Parc Asterix");

	int nombreVisiteurs;
	int heureOuverture;
	int heureFermeture;

	// Demander à l'utilisateur l'heure d'ouverture du parc (entre 0 et 24)
	do {
		std::cout << "Entrez l'heure d'ouverture du parc (nombre entier compris entre 0 et 24) : ";
		std::cin >> heureOuverture;
	} while (heureOuverture < 0 || heureOuverture > 24);

	// Afficher l'heure d'ouverture
	std::cout << "Heure d'ouverture : " << heureOuverture << "h00" << std::endl;

	// Demander à l'utilisateur l'heure de fermeture du parc (entre 0 et 24 et supérieure à l'heure d'ouverture)
	do {
		std::cout << "Entrez l'heure de fermeture du parc (nombre entier compris entre 0 et 24 et superieure a l'heure d'ouverture) : ";
		std::cin >> heureFermeture;
	} while (heureFermeture < heureOuverture || heureFermeture > 24);

	// Afficher l'heure de fermeture
	std::cout << "Heure de fermeture : " << heureFermeture << "h00" << std::endl;

	// Demander à l'utilisateur le nombre de visiteurs (nombre positif)
	do {
		std::cout << "Entrez le nombre de visiteurs : ";
		std::cin >> nombreVisiteurs;
	} while (nombreVisiteurs < 0);

	// Afficher le nombre de visiteurs
	std::cout << "Nombre de visiteurs : " << nombreVisiteurs << std::endl;

	// Création d'une instance du Parc Astérix
	Parc monParc("Parc Asterix");

	Attraction cesar("Le defi de Cesar", 80, 20, { 0, 2 });
	monParc.AjouterAttraction(cesar);

	Attraction romusrapidus("Romus et Rapidus", 9, 2, { -3, 3 });
	monParc.AjouterAttraction(romusrapidus);

	Attraction pegase("Pegase express", 20, 3, { -8, 5 });
	monParc.AjouterAttraction(pegase);

	Attraction grandsplash("Le grand Splash", 20, 6, { 2, 6 });
	monParc.AjouterAttraction(grandsplash);

	Attraction gyrofolix("Chez Gyrofolix", 32, 4, { 6, 4 });
	monParc.AjouterAttraction(gyrofolix);

	Attraction traceDuHourra("La trace du Hourra", 14, 2, { 5,8 });
	monParc.AjouterAttraction(traceDuHourra);

	Attraction toutatis("Toutatis", 20, 3, { 9, 3 });
	monParc.AjouterAttraction(toutatis);

	Attraction epidemais("Epidemais croisiere", 16, 10, { 0, 8 });
	monParc.AjouterAttraction(epidemais);

	Attraction menhir("Menhir Express", 4, 5, { 3, 9 });
	monParc.AjouterAttraction(menhir);

	Attraction chevaux("Les chevaux du Roy", 20, 5, { 0, 14 });
	monParc.AjouterAttraction(chevaux);

	Attraction attentionMenhir("Attention Menhir", 300, 30, { 4, 12 });
	monParc.AjouterAttraction(attentionMenhir);

	Attraction oziris("Oz'iris", 32, 3, { 8, 14 });
	monParc.AjouterAttraction(oziris);

	Attraction oxygenarium("L'Oxygenarium", 6, 3, { 8, 14 });
	monParc.AjouterAttraction(oxygenarium);

	Attraction galere("La galere", 54, 13, { -5, 11 });
	monParc.AjouterAttraction(galere);

	Attraction goudurix("Goudurix", 28, 3, { -7,16 });
	monParc.AjouterAttraction(goudurix);

	Attraction discobelix("Discobelix", 40, 5, { -12, 11 });
	monParc.AjouterAttraction(discobelix);

	Attraction tonerre("Tonnere 2 Zeus", 26, 3, { -12, 11 });
	monParc.AjouterAttraction(tonerre);

	//Création des visiteurs
	std::vector<Visiteur> visiteurs;
	std::vector<Attraction>& attractions = monParc.GetAttractions();
	for (int i = 0; i < nombreVisiteurs; ++i) {
		std::string nomVisiteur = "Visiteur " + std::to_string(i + 1);
		Visiteur visiteur(nomVisiteur, attractions);
		visiteurs.push_back(visiteur);
		monParc.AjouterVisiteur(visiteur);
	}

	// Simulation de la journée
	monParc.simulerJournee(heureOuverture, heureFermeture, window);

	// Libération de la mémoire des visiteurs
	monParc.LibérerVisiteurs();

	return 0;
}