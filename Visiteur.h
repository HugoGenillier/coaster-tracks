// Visiteur.h
#ifndef VISITEUR_H
#define VISITEUR_H

#include <string>
#include "Structure.hpp"
#include <iostream>

// D�claration avanc�e de la classe Attraction
class Attraction;

class Visiteur {
public:
	// Constructeur
	Visiteur(std::string nom);

	// M�thodes publiques
	void AfficherDetails() const;
	void ActiverVisiteur();
	void DeplacerVersAttraction();
	void FaireDecision();
	std::string GetNom() const;

	// Destructeur
	~Visiteur();

private:
	std::string Nom;
	Coordonnees Position;
	int TempsAttendu;
	Attraction* Objectif;
	EtatVisiteur Etat;
};

#endif // VISITEUR_H
