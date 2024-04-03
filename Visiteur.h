// Visiteur.h
#ifndef VISITEUR_H
#define VISITEUR_H

#include <string>
#include "Structure.hpp"
#include <utility>
#include <iostream>
#include <algorithm> 
#include <ctime> 
#include <random>
#include "Attraction.h"

// Déclaration avancée de la classe Attraction pour éviter les inclusion mutuelles
class Attraction;

class Visiteur {
public:
	// Constructeur
	Visiteur();
	Visiteur(std::string nom,std::vector<Attraction>& attractions);
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
	std::string GetActions() const;

	// Destructeur
	~Visiteur();

private:
	std::string Nom;
	//position dans le parc (x,y)
	Coordonnees Position;
	//Temps total que le visiteur à passé à attendre dans les files d'attentes
	int TempsAttendu;
	//L'attraction vers laquelle se dirige le visiteur
	Attraction* Objectif;
	//Etat du visiteur (en marche, en décision ou en attente)
	EtatVisiteur Etat;
	//Le visiteur connais les attractions du parc ainsi que leur temps d'attente, Il sait si il a déjà fait une attraction et si elle fait partie des ses favoris
	std::vector<std::tuple<Attraction*, bool, bool>> ListeAttractions;
};

#endif // VISITEUR_H
