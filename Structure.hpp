// Structure.hpp
#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include <cmath>

//Ce fichier est d�di� aux structures de donn�es mises en place comme le syst�me de coordon�es ou bien les �tats des visiteurs

// Structure Coordonnees
struct Coordonnees {
	double x;
	double y;

	// M�thode pour calculer la distance entre deux points du parc
	int distance(const Coordonnees& autre) const {
		// calcul de la distance euclidienne entre deux points dans un plan
		double distance = sqrt((x - autre.x) * (x - autre.x) + (y - autre.y) * (y - autre.y));
		// Arrondir � l'entier le plus proche pour ne pas d�passer une attraction dans les d�placements par exemple
		return static_cast<int>(round(distance));
	}

	// Surcharge de l'op�rateur "==" pour permettre la comparaison de coordonn�es
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
