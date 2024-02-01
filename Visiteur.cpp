#include "Visiteur.h"
#include <iostream>
#include "Structure.hpp"
using namespace std;

// Constructeur
Visiteur::Visiteur(std::string nom) : Nom(nom), TempsAttendu(0) {}

// M�thode publique
void Visiteur::AfficherDetails() const {
	cout << "Nom : " << Nom << ", Temps total d'attente : " << TempsAttendu << endl;
}

// Destructeur
Visiteur::~Visiteur() {}


