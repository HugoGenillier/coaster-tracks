#include "Parc.h"
#include "Attraction.h"
#include "Visiteur.h"
#include <iostream>
#include "Structure.hpp"
using namespace std;

// Constructeur
Parc::Parc(std::string nom) : Nom(nom) {
	vector<Visiteur> visiteurs;
	Visiteurs = visiteurs;
	vector<Attraction> attractions;
	Attractions = attractions;
}

// Méthode publique
void Parc::AfficherDetails() const {
	cout << "Nom : " << Nom << endl;
}

// Destructeur
Parc::~Parc() {}