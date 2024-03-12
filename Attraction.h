#ifndef ATTRACTION_H
#define ATTRACTION_H

#include <queue>
#include <string>
#include "Structure.hpp"
#include <iostream>
#include "Horloge.h"

// Déclaration avancée de la classe Visiteur
class Visiteur;

class Attraction {
public:
	// Constructeurs
	Attraction();
	Attraction(const std::string& nom, int capacite, int tempsFonctionnement);

	// Méthodes publiques
	void AfficherDetails() const;
	void ReduireTempsFonctionnementRestant();
	void RetirerVisiteursTermines();
	void AjouterVisiteur(Visiteur* visiteur); // Utilisation de pointeurs
	int GetTempsFonctionnementRestant() const;
	int TempsAttenteEstime() const;
	std::string GetNom() const;
	const Coordonnees& GetPosition() const;
	void AvancerTour();
	int GetNombreVisiteur() const;

	std::queue<Visiteur*>& GetFileAttente();

	// Destructeur
	~Attraction();

private:
	// Membres privés
	std::string Nom;
	Coordonnees Position;
	int Capacite;
	int TempsTour;
	int TempsFonctionnementRestant;
	std::queue<Visiteur*> FileAttente; // Utilisation de pointeurs
};

#endif // ATTRACTION_H
