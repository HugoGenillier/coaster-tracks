#include "Visiteur.h"

// Constructeur
Visiteur::Visiteur(std::string nom) : Nom(nom), TempsAttendu(0) {
	Position.x = 0;
	Position.y = 0;
}

// Méthode publique
void Visiteur::AfficherDetails() const {
	cout << "Nom : " << Nom << ", Temps total d'attente : " << TempsAttendu << endl;
}

void Visiteur::ActiverVisiteur() const {

}

void Visiteur::DeplacerVersObjectif() const {
	int distance = Position.distance(ObjectifActuel.Position);

}

void Visiteur::FaireDecision() const {

}

std::string Visiteur::GetNom() const {
	return Nom;
}

// Destructeur
Visiteur::~Visiteur() {}


