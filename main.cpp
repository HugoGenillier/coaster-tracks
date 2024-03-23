#include "Parc.h"
#include "Attraction.h"
#include "Visiteur.h"
#include "Horloge.h"

int main() {
	// Cr�ation d'une instance de parc
	Parc monParc("Parc Ast�rix");


	Attraction cesar("Le d�fi de C�sar", 80, 20, { 0, 2 });
	monParc.AjouterAttraction(cesar);

	Attraction romusrapidus("Romus et Rapidus", 9, 2, { -3, 3 });
	monParc.AjouterAttraction(romusrapidus);

	Attraction pegase("P�gase express", 20, 3, { -8, 5 });
	monParc.AjouterAttraction(pegase);

	Attraction grandsplash("Le grand Splash", 20, 6, { 2, 6 });
	monParc.AjouterAttraction(grandsplash);

	Attraction gyrofolix("Chez Gyrofolix", 32, 4, { 6, 4 });
	monParc.AjouterAttraction(gyrofolix);

	Attraction traceDuHourra("La trace du Hourra", 14, 2, { 5,8 });
	monParc.AjouterAttraction(traceDuHourra);

	Attraction toutatis("Toutatis", 20, 3, { 9, 3 });
	monParc.AjouterAttraction(toutatis);

	Attraction epidemais("Epidema�s croisi�re", 16, 10, { 0, 8 });
	monParc.AjouterAttraction(epidemais);

	Attraction menhir("Menhir Express", 4, 5, { 3, 9 });
	monParc.AjouterAttraction(menhir);

	Attraction chevaux("Les chevaux du Roy", 20, 5, { 0, 14 });
	monParc.AjouterAttraction(chevaux);

	Attraction attentionMenhir("Attention Menhir", 300, 30, { 4, 12 });
	monParc.AjouterAttraction(attentionMenhir);

	Attraction oziris("Oz'iris", 32, 3, { 8, 14 });
	monParc.AjouterAttraction(oziris);

	Attraction oxygenarium("L'Oxyg�narium", 6, 3, { 8, 14 });
	monParc.AjouterAttraction(oxygenarium);

	Attraction galere("La gal�re", 54, 13, { -5, 11 });
	monParc.AjouterAttraction(galere);

	Attraction goudurix("Goudurix", 28, 3, { -7,16 });
	monParc.AjouterAttraction(goudurix);

	Attraction discobelix("Discobelix", 40, 5, { -12, 11 });
	monParc.AjouterAttraction(discobelix);

	Attraction tonerre("Tonn�re 2 Zeus", 26, 3, { -12, 11 });
	monParc.AjouterAttraction(tonerre);

	// Cr�ation de visiteurs
	std::vector<Visiteur> visiteurs;
	std::vector<Attraction>& attractions = monParc.GetAttractions(); // Obtenir le vecteur d'attractions
	for (int i = 0; i < 3000; ++i) {
		std::string nomVisiteur = "Visiteur " + std::to_string(i + 1);
		Visiteur visiteur(nomVisiteur, attractions); // Passer le vecteur d'attractions au constructeur du visiteur
		visiteurs.push_back(visiteur);
		monParc.AjouterVisiteur(visiteur); // Ajouter le visiteur au vecteur de visiteurs du parc
	}

	// Simulation de la journ�e
	monParc.simulerJournee(10, 18);

	// Lib�ration de la m�moire des visiteurs
	monParc.Lib�rerVisiteurs();

	return 0;
}