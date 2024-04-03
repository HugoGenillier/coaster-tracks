#ifndef ATTRACTION_H
#define ATTRACTION_H

#include <queue>
#include <string>
#include "Structure.hpp"
#include <iostream>
#include "Horloge.h"

// D�claration avanc�e de la classe Visiteur pour �viter d'avoir des probl�mes d'inclusion mutuelle
class Visiteur;

class Attraction {
public:

	Attraction();
	Attraction(const std::string& nom, int capacite, int tempsFonctionnement, Coordonnees positon);
	void AfficherDetails() const;
	void RetirerVisiteursTermines();
	void AjouterVisiteur(Visiteur* visiteur);
	int GetTempsFonctionnementRestant() const;
	int TempsAttenteEstime() const;
	std::string GetNom() const;
	const Coordonnees& GetPosition() const;
	void AvancerTour();
	int GetNombreVisiteur() const;
	std::queue<Visiteur*>& GetFileAttente();

	~Attraction();

private:
	std::string Nom;
	//position dans le parc (x,y)
	Coordonnees Position;
	//Nombre de personne que l'attraction peut embarquer par tour de man�ge
	int Capacite;
	//Temps d'un tour de man�ge
	int TempsTour;
	//Temps restant avant la fin du tour actuel
	int TempsFonctionnementRestant;
	//File d'attente de l'attraction, principe "First in first out"
	std::queue<Visiteur*> FileAttente;
};

#endif // ATTRACTION_H
