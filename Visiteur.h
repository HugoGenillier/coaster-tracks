// Visiteur.h
#ifndef VISITEUR_H
#define VISITEUR_H

#include <string>
#include "Structure.hpp"
#include <utility> // pour std::pair
#include <iostream>
#include <algorithm> // Pour utiliser std::random_shuffle
#include <ctime>     // Pour initialiser le générateur de nombres aléatoires
#include <random>
// Inclure l'en-tête de la classe Attraction
#include "Attraction.h"

// Déclaration avancée de la classe Attraction
class Attraction;

class Visiteur {
public:
	// Constructeur
	Visiteur();
	Visiteur(std::string nom,std::vector<Attraction>& attractions);

	// Méthodes publiques
	void AfficherDetails() const;
	void ActiverVisiteur();
	void DeplacerVersAttraction();
	void FaireDecision();
	std::string GetNom() const;
	void AjouterAttractionVisitee(Attraction* attraction);
	void ChangerComportement(EtatVisiteur nouvelEtat);
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
	std::vector<std::tuple<Attraction*, bool, bool>> ListeAttractions;
};

#endif // VISITEUR_H
