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
};


// Ajoutez d'autres structures au besoin...

#endif // STRUCTURES_HPP
