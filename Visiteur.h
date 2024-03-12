// Personne.hpp

#ifndef VISITEUR_HPP
#define VISITEUR_HPP

#include <string>
#include "Structure.hpp"
#include <iostream>
#include "Horloge.h"
#include "Attraction.h"
using namespace std;

class Visiteur {
public:
	// Constructeur
	Visiteur(std::string nom);

	// Méthode publique
	void AfficherDetails() const;

	void ActiverVisiteur();

	void DeplacerVersAttraction();

	void FaireDecision();

	std::string GetNom() const;

	// Destructeur
	~Visiteur();

private:
	// Membres privés
	std::string Nom;
	Coordonnees Position;
	int TempsAttendu;
	Attraction Objectif;
	EtatVisiteur Etat;
};

#endif // PERSONNE_HPP

