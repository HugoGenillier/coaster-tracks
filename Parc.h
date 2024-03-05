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
#include <mutex>
using namespace std;


class Parc {
public:
	// Constructeur
	Parc(std::string nom);

	// Méthode publique
	void AfficherDetails() const;

	void simulerJournee(int heureOuverture, int heureFermeture);

	void AjouterAttraction(const Attraction& attraction);

	// Destructeur
	~Parc();

private:
	// Membres privés
	std::string Nom;
	std::vector<Visiteur> Visiteurs;
	std::vector<Attraction> Attractions;
	std::mutex mutexHorloge; // Mutex pour synchroniser l'accès à l'horloge
};

#endif // PARC_HPP

