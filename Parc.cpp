#include "Parc.h"
#include "Attraction.h"
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

		// Afficher les d�tails de chaque attraction
		for (const auto& attraction : Attractions) {
			std::cout << "Attraction : " << attraction.GetNom() << ", Temps d'attente estim� : " << attraction.TempsAttenteEstime() << " minutes\n";
		}

		// Attendre une minute (simulation de l'heure)
		std::this_thread::sleep_for(std::chrono::seconds(1)); // Attendre 1 seconde pour simuler une minute
	}

	std::cout << "Fin de la journ�e dans le parc\n";
}



// Destructeur
Parc::~Parc() {}