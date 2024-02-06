#ifndef PARC_HPP
#define PARC_HPP
#include "Visiteur.h"
#include "Attraction.h"
#include <queue>
#include <string>
#include <chrono>
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
	std::chrono::system_clock::time_point heureOuverture;
	std::chrono::system_clock::time_point heureFermeture;
};

#endif // PARC_HPP

