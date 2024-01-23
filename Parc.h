#ifndef PARC_HPP
#define PARC_HPP
#include "Visiteur.h"
#include "Attraction.h"
#include <queue>
#include <string>

class Parc {
public:
	// Constructeur
	Parc(std::string nom);

	// M�thode publique
	void AfficherDetails() const;

	// Destructeur
	~Attraction();

private:
	// Membres priv�s
	std::string Nom;
	std::vector<Visiteur> Visiteurs;
	std::vector<Attraction> Attractions;
};

#endif // PERSONNE_HPP

