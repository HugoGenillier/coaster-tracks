// Structure.hpp
#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include <cmath>

//Ce fichier est dédié aux structures de données mises en place comme le système de coordonées ou bien les états des visiteurs

// Structure Coordonnees
struct Coordonnees {
	double x;
	double y;

	// Méthode pour calculer la distance entre deux points du parc
	int distance(const Coordonnees& autre) const {
		// calcul de la distance euclidienne entre deux points dans un plan
		double distance = sqrt((x - autre.x) * (x - autre.x) + (y - autre.y) * (y - autre.y));
		// Arrondir à l'entier le plus proche pour ne pas dépasser une attraction dans les déplacements par exemple
		return static_cast<int>(round(distance));
	}

	// Surcharge de l'opérateur "==" pour permettre la comparaison de coordonnées
	bool operator==(const Coordonnees& autre) const {
		return x == autre.x && y == autre.y;
	}
};

// Définition de l'énumération pour les états du visiteur
enum class EtatVisiteur {
	EnMarche,
	EnFileAttente,
	EnDecision
};

#endif // STRUCTURES_HPP
