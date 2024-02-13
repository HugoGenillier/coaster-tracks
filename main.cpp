#include "main.h"
#include "Parc.h"

// Fonction pour afficher l'heure à intervalle régulier
void afficherHeure(Horloge& horloge) {
	while (true) {
		// Avancer d'une heure dans l'horloge
		horloge.avancerTemps(); // Avance d'une heure

		// Récupérer l'heure et les minutes
		int heure = horloge.getHeure();
		int minute = horloge.getMinute();

		// Afficher l'heure
		std::cout << "Heure : " << heure << "h" << minute << std::endl;

		// Attendre une minute réelle
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main() {
	// Créer une instance de l'horloge
	Horloge horloge(9, 12);

	// Démarrer la simulation du temps (avec un défilement plus lent)
	horloge.start();

	// Lancer un thread pour afficher l'heure
	std::thread affichageThread(afficherHeure, std::ref(horloge));

	// Attendre que l'utilisateur appuie sur une touche pour terminer le programme
	std::cin.get();

	// Arrêter la simulation du temps
	horloge.stop();

	// Attendre que le thread d'affichage se termine
	affichageThread.join();

	return 0;
}