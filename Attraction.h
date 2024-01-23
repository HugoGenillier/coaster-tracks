// Attraction.hpp

#ifndef ATTRACTION_HPP
#define ATTRACTION_HPP
#include "Visiteur.h"
#include <queue>
#include <string>

class Attraction {
public:
	// Constructeur
	Attraction(std::string nom, int capacite);

	// M�thode publique
	void AfficherDetails() const;

	// Destructeur
	~Attraction();

private:
	// Membres priv�s
	std::string Nom;
	int TempsAttenteActuel;
	int Capacite;
	std::queue<Visiteur> FileAttente;
};

#endif // ATTRACTION_HPP

