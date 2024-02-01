// Personne.hpp

#ifndef VISITEUR_HPP
#define VISITEUR_HPP
#include <string>
#include "Structure.hpp"

class Visiteur {
public:
	// Constructeur
	Visiteur(std::string nom);

	// Méthode publique
	void AfficherDetails() const;

	// Destructeur
	~Visiteur();

private:
	// Membres privés
	std::string Nom;
	int TempsAttendu;
};

#endif // PERSONNE_HPP

