#ifndef PARC_HPP
#define PARC_HPP

#include <queue>
#include <string>
#include <chrono>
#include "Structure.hpp"
#include "Attraction.h"
#include "Visiteur.h"
#include <iostream>
#include <thread>
using namespace std;


class Parc {
public:
	// Constructeur
	Parc(std::string nom, int ouverture, int fermeture);

	// Méthode publique
	void AfficherDetails() const;

	void afficherHeure();

	void simulerUneJournee();


	// Destructeur
	~Parc();

private:
	// Membres privés
	std::string Nom;
	Horloge horloge;
	std::vector<Visiteur> Visiteurs;
	std::vector<Attraction> Attractions;
	std::chrono::system_clock::time_point heureOuverture;
	std::chrono::system_clock::time_point heureFermeture;
};

#endif // PARC_HPP

