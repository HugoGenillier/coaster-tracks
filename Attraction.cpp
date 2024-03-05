#include "Attraction.h"


// Constructeur de la classe Attraction
Attraction::Attraction(const std::string& nom, int capacite, int tempsFonctionnement)
	: Nom(nom), Capacite(capacite), TempsFonctionnementRestant(tempsFonctionnement), TempsTour(tempsFonctionnement) {}


// M�thode publique
void Attraction::AfficherDetails() const {
	int TempsAttenteActuel = TempsAttenteEstime();
	cout << "Nom : " << Nom << ", Capacite : " << Capacite << ", Temps d'attente actuel : " << TempsAttenteActuel << endl;
}

void Attraction::ReduireTempsFonctionnementRestant() {
	if (TempsFonctionnementRestant > 0) {
		TempsFonctionnementRestant--;
	}
}

void Attraction::RetirerVisiteursTermines() {
	// Tant que la file d'attente n'est pas vide et qu'il reste des places disponibles dans l'attraction
	while (!FileAttente.empty() && Capacite > 0) {
		// Retirer le visiteur en t�te de file
		FileAttente.pop();

		// D�cr�menter la capacit� de l'attraction
		Capacite--;
	}
}

void Attraction::AjouterVisiteur(const Visiteur& visiteur) {
	// Ajouter le visiteur � la file d'attente
	FileAttente.push(visiteur);
}

int Attraction::GetTempsFonctionnementRestant() const {
	return TempsFonctionnementRestant;
}

int Attraction::TempsAttenteEstime() const {
	// Calculer le nombre de visiteurs dans la file d'attente
	int nombreVisiteurs = FileAttente.size();

	// V�rifier si la file d'attente est vide ou si la capacit� de l'attraction est nulle
	if (nombreVisiteurs == 0 || Capacite == 0) {
		return 0; // Pas d'attente si la file est vide ou si la capacit� est nulle
	}

	// Calculer le temps d'attente estim� en fonction du nombre de visiteurs dans la file, de la capacit� et du temps d'un tour
	int tempsAttente = (nombreVisiteurs / Capacite) * TempsTour;
	return tempsAttente;
}

// Destructeur
Attraction::~Attraction() {}
