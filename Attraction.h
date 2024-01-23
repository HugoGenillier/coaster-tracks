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

	// Méthode publique
	void AfficherDetails() const;

	// Destructeur
	~Attraction();

private:
	// Membres privés
	std::string Nom;
	int TempsAttenteActuel;
	int Capacite;
	std::queue<Visiteur> FileAttente;
};

#endif // ATTRACTION_HPP

