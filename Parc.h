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
#include <SFML/Graphics.hpp> 

class Parc {
public:
	// Constructeur
	Parc(std::string nom);

	void AfficherDetails() const;
	void simulerJournee(int heureOuverture, int heureFermeture, sf::RenderWindow& window); 
	void AjouterAttraction(const Attraction& attraction);

	//Getter pour avoir la liste des attractions du parc
	std::vector<Attraction>& GetAttractions() {
		return Attractions;
	}

	//M�thode pour ajouter un visiteur dans le parc
	void AjouterVisiteur(const Visiteur& visiteur) {
		Visiteurs.push_back(visiteur);
	}

	void Lib�rerVisiteurs();

	// Destructeur
	~Parc();

private:
	std::string Nom;
	//liste des visiteurs
	std::vector<Visiteur> Visiteurs;
	//liste des attractions
	std::vector<Attraction> Attractions;
	//Mutex pour synchroniser l'acc�s � l'horloge car elle s'ex�cute dans un thread � part
	std::mutex mutexHorloge;
};

#endif // PARC_HPP