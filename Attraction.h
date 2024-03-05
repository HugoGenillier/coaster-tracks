// Attraction.hpp

#ifndef ATTRACTION_HPP
#define ATTRACTION_HPP

#include "Visiteur.h"
#include <queue>
#include <string>
#include "Structure.hpp"
#include <iostream>
#include "Horloge.h"
using namespace std;

class Attraction {
public:
	// Constructeur
	Attraction(const std::string& nom, int capacite, int tempsFonctionnement);

	// Méthode publique
	void AfficherDetails() const;

	void ReduireTempsFonctionnementRestant();
	void RetirerVisiteursTermines();
	void AjouterVisiteur(const Visiteur& visiteur);
	int GetTempsFonctionnementRestant() const;
	int TempsAttenteEstime() const;
	string GetNom() const;

	// Destructeur
	~Attraction();

private:
	// Membres privés
	std::string Nom;
	Coordonnees Position;
	int Capacite;
	int TempsTour;
	int TempsFonctionnementRestant;
	std::queue<Visiteur> FileAttente;
};

#endif // ATTRACTION_HPP

