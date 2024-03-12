// Structure.hpp
#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include <cmath>

// Structure Coordonnees
struct Coordonnees {
	double x;
	double y;

	// M�thode pour calculer la distance entre deux points
	int distance(const Coordonnees& autre) const {
		// Utilisation de la formule de distance euclidienne entre deux points dans un plan
		double distance = sqrt((x - autre.x) * (x - autre.x) + (y - autre.y) * (y - autre.y));
		// Arrondir � l'entier le plus proche
		return static_cast<int>(round(distance));
	}

	// Surcharge de l'op�rateur ==
	bool operator==(const Coordonnees& autre) const {
		return x == autre.x && y == autre.y;
	}
};

// D�finition de l'�num�ration pour les �tats du visiteur
enum class EtatVisiteur {
	EnMarche,
	EnFileAttente,
	EnDecision
};

#endif // STRUCTURES_HPP
