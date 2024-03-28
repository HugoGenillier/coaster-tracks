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

// Définition des couleurs
#define RESET   "\033[0m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"    
#define MAGENTA "\033[35m"     
#define CYAN    "\033[36m"      
#define WHITE   "\033[37m"      


class Parc {
public:
	// Constructeur
	Parc(std::string nom);

	// Méthode publique
	void AfficherDetails() const;

	void simulerJournee(int heureOuverture, int heureFermeture);

	void AjouterAttraction(const Attraction& attraction);

	std::vector<Attraction>& GetAttractions() {
		return Attractions;
	}

	void AjouterVisiteur(const Visiteur& visiteur) {
		Visiteurs.push_back(visiteur);
	}

	void LibérerVisiteurs();

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