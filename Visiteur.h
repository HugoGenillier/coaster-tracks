// Visiteur.h
#ifndef VISITEUR_H
#define VISITEUR_H

#include <string>
#include "Structure.hpp"
#include <utility> // pour std::pair
#include <iostream>

// Inclure l'en-t�te de la classe Attraction
#include "Attraction.h"

// D�claration avanc�e de la classe Attraction
class Attraction;

class Visiteur {
public:
	// Constructeur
	Visiteur();
	Visiteur(std::string nom, std::vector<Attraction>& attractions);

	// M�thodes publiques
	void AfficherDetails() const;
	void ActiverVisiteur();
	void DeplacerVersAttraction();
	void FaireDecision();
	std::string GetNom() const;
	const Coordonnees& GetPosition() const {
		return Position;
	}

	// Destructeur
	~Visiteur();

private:
	std::string Nom;
	Coordonnees Position;
	int TempsAttendu;
	Attraction* Objectif;
	EtatVisiteur Etat;
	std::vector<std::pair<Attraction*, bool>> ListeAttractions;
};

#endif // VISITEUR_H
