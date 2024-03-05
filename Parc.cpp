#include "Parc.h"
#include <iomanip> // Inclure la bibliothèque iomanip pour utiliser setw

// Constructeur
Parc::Parc(std::string nom) : Nom(nom), Attractions(), Visiteurs() {}


// Méthode publique
void Parc::AfficherDetails() const {
	cout << "Nom : " << Nom << endl;
}

void Parc::simulerJournee(int heureOuverture, int heureFermeture) {
	std::cout << "Simulation de la journée dans le parc de " << heureOuverture << "h à " << heureFermeture << "h\n";

	// Création de l'horloge au moment du démarrage de la simulation de la journée
	Horloge horloge(heureOuverture, heureFermeture);
	horloge.start();

	while (horloge.estEnCours()) {
		std::lock_guard<std::mutex> lock(mutexHorloge); // Verrouiller l'accès à l'horloge

		int heure = horloge.getHeure();
		int minute = horloge.getMinute();
		std::system("cls");
		std::cout << "Heure : " << std::setw(2) << std::setfill('0') << heure << "h"
			<< std::setw(2) << std::setfill('0') << minute << "\n";

		// Mettre à jour le temps de fonctionnement restant de chaque attraction
		for (auto& attraction : Attractions) {
			if (attraction.getTempsFonctionnementRestant() > 0) {
				attraction.reduireTempsFonctionnementRestant();
			}

			// Si le temps de fonctionnement restant atteint zéro, traiter les visiteurs
			if (attraction.getTempsFonctionnementRestant() == 0) {
				// Retirer les visiteurs qui ont terminé leur tour
				attraction.retirerVisiteursTermines();

				// Ajouter de nouveaux visiteurs à partir de la file d'attente
				attraction.ajouterVisiteurs(fileAttente);
			}
		}

		// Attendre une minute (simulation de l'heure)
		std::this_thread::sleep_for(std::chrono::seconds(1)); // Attendre 1 seconde pour simuler une minute
	}

	std::cout << "Fin de la journée dans le parc\n";
}




// Destructeur
Parc::~Parc() {}