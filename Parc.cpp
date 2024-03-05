#include "Parc.h"
#include <iomanip> // Inclure la biblioth�que iomanip pour utiliser setw

// Constructeur
Parc::Parc(std::string nom) : Nom(nom), Attractions(), Visiteurs() {}


// M�thode publique
void Parc::AfficherDetails() const {
	cout << "Nom : " << Nom << endl;
}

void Parc::simulerJournee(int heureOuverture, int heureFermeture) {
	std::cout << "Simulation de la journ�e dans le parc de " << heureOuverture << "h � " << heureFermeture << "h\n";

	// Cr�ation de l'horloge au moment du d�marrage de la simulation de la journ�e
	Horloge horloge(heureOuverture, heureFermeture);
	horloge.start();

	while (horloge.estEnCours()) {
		std::lock_guard<std::mutex> lock(mutexHorloge); // Verrouiller l'acc�s � l'horloge

		int heure = horloge.getHeure();
		int minute = horloge.getMinute();
		std::system("cls");
		std::cout << "Heure : " << std::setw(2) << std::setfill('0') << heure << "h"
			<< std::setw(2) << std::setfill('0') << minute << "\n";

		// Mettre � jour le temps de fonctionnement restant de chaque attraction
		for (auto& attraction : Attractions) {
			if (attraction.getTempsFonctionnementRestant() > 0) {
				attraction.reduireTempsFonctionnementRestant();
			}

			// Si le temps de fonctionnement restant atteint z�ro, traiter les visiteurs
			if (attraction.getTempsFonctionnementRestant() == 0) {
				// Retirer les visiteurs qui ont termin� leur tour
				attraction.retirerVisiteursTermines();

				// Ajouter de nouveaux visiteurs � partir de la file d'attente
				attraction.ajouterVisiteurs(fileAttente);
			}
		}

		// Attendre une minute (simulation de l'heure)
		std::this_thread::sleep_for(std::chrono::seconds(1)); // Attendre 1 seconde pour simuler une minute
	}

	std::cout << "Fin de la journ�e dans le parc\n";
}




// Destructeur
Parc::~Parc() {}