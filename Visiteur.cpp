#include "Visiteur.h"

// Constructeur
Visiteur::Visiteur(std::string nom) : Nom(nom), TempsAttendu(0) {}

// Méthode publique
void Visiteur::AfficherDetails() const {
	cout << "Nom : " << Nom << ", Temps total d'attente : " << TempsAttendu << endl;
}

std::string Visiteur::GetNom() const {
	return Nom;
}

// Destructeur
Visiteur::~Visiteur() {}


