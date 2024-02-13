#include "Parc.h"

// Constructeur
Parc::Parc(std::string nom, int ouverture, int fermeture) : Nom(nom), horloge(ouverture, fermeture) {
	vector<Visiteur> visiteurs;
	Visiteurs = visiteurs;
	vector<Attraction> attractions;
	Attractions = attractions;
}

// M�thode publique
void Parc::AfficherDetails() const {
	cout << "Nom : " << Nom << endl;
}

void Parc::simulerUneJournee() {
	// Boucle pour simuler une journ�e compl�te
	while (horloge.getHeure() != 23 || horloge.getMinute() != 59) {
		// Avancer d'une minute
		horloge.avancerTemps();

		// Afficher l'heure actuelle
		afficherHeure();

		// Effectuer d'autres op�rations de simulation pour chaque minute
	}
}

void Parc::afficherHeure() {
	std::cout << "Heure actuelle : " << horloge.getHeure() << "h" << horloge.getMinute() << std::endl;
}

// Destructeur
Parc::~Parc() {}