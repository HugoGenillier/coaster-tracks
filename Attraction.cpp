#include "Attraction.h"


// Constructeur
Attraction::Attraction(std::string nom, int capacite) : Nom(nom), Capacite(capacite), TempsAttenteActuel(0) {
	queue<Visiteur> queueVide;
	FileAttente = queueVide;
}

// Méthode publique
void Attraction::AfficherDetails() const {
	cout << "Nom : " << Nom << ", Capacite : " << Capacite << ", Temps d'attente actuel : " << TempsAttenteActuel << endl;
}

// Destructeur
Attraction::~Attraction() {}
