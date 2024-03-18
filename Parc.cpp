#include "Parc.h"
#include <iomanip> // Inclure la biblioth�que iomanip pour utiliser setw

// Constructeur
Parc::Parc(std::string nom) : Nom(nom), Attractions(), Visiteurs() {}


// M�thode publique
void Parc::AfficherDetails() const {
	cout << "Nom : " << Nom << endl;
}


void Parc::AjouterAttraction(const Attraction& attraction) {
	Attractions.push_back(attraction); // Ajoute l'attraction � la liste des attractions du parc
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

		// Faire avancer le temps dans chaque attraction
		for (auto& attraction : Attractions) {
			attraction.AvancerTour(); // Faire avancer la file d'attente et le temps d'attente estim� de l'attraction
			std::cout << "Attraction : " << attraction.GetNom() << ", Temps d'attente estim� : " << attraction.TempsAttenteEstime() << " minutes\n";
			std::cout << "Nombre de visiteurs dans la file d'attente : " << attraction.GetNombreVisiteur() << std::endl;
		}

		// Activer les visiteurs
		for (auto& visiteur : Visiteurs) {
			visiteur.ActiverVisiteur(); // Activer le visiteur
		}

		// Attendre une seconde (simulation de l'heure)
		std::this_thread::sleep_for(std::chrono::seconds(1)); // Attendre 1 seconde pour simuler une minute
	}

	std::cout << "Fin de la journ�e dans le parc\n";
}

void Parc::Lib�rerVisiteurs() {
	for (Attraction& attraction : Attractions) {
		std::queue<Visiteur*>& fileAttente = attraction.GetFileAttente();
		while (!fileAttente.empty()) {
			Visiteur* visiteur = fileAttente.front();
			delete visiteur; // Lib�rer la m�moire allou�e pour chaque visiteur
			fileAttente.pop();
		}
	}
}


// Destructeur
Parc::~Parc() {}