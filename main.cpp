#include "main.h"
#include "Parc.h"

// Fonction pour afficher l'heure � intervalle r�gulier
void afficherHeure(Horloge& horloge) {
	while (true) {
		// Avancer d'une heure dans l'horloge
		horloge.avancerTemps(); // Avance d'une heure

		// R�cup�rer l'heure et les minutes
		int heure = horloge.getHeure();
		int minute = horloge.getMinute();

		// Afficher l'heure
		std::cout << "Heure : " << heure << "h" << minute << std::endl;

		// Attendre une minute r�elle
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main() {
	// Cr�er une instance de l'horloge
	Horloge horloge(9, 12);

	// D�marrer la simulation du temps (avec un d�filement plus lent)
	horloge.start();

	// Lancer un thread pour afficher l'heure
	std::thread affichageThread(afficherHeure, std::ref(horloge));

	// Attendre que l'utilisateur appuie sur une touche pour terminer le programme
	std::cin.get();

	// Arr�ter la simulation du temps
	horloge.stop();

	// Attendre que le thread d'affichage se termine
	affichageThread.join();

	return 0;
}