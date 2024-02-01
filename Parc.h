#ifndef PARC_HPP
#define PARC_HPP
#include "Visiteur.h"
#include "Attraction.h"
#include <queue>
#include <string>
#include "Structure.hpp"

class Parc {
public:
	// Constructeur
	Parc(std::string nom);

	// M�thode publique
	void AfficherDetails() const;

	// Destructeur
	~Parc();

private:
	// Membres priv�s
	std::string Nom;
	std::vector<Visiteur> Visiteurs;
	std::vector<Attraction> Attractions;
};

#endif // PARC_HPP

