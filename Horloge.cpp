#include "Horloge.h"
#pragma once
#include <chrono>
#include "Horloge.h"

Horloge::Horloge(int heureDebut, int heureFin) : heureDebut(heureDebut), heureFin(heureFin), running(false) {
	// Initialiser l'horloge � l'heure de d�but rentr�e en param�tre
	tempsActuel = std::chrono::system_clock::time_point{};
	tempsActuel += std::chrono::hours(heureDebut - 1);
}

//M�thode pour lancer l'horloge qui avance d'une minute toutes les secondes
void Horloge::start() {
	running = true;
	std::thread([this]() {
		while (running) {
			// Avancer d'une minute
			avancerTemps();

			// V�rifier si l'heure actuelle est �gale � l'heure de fermeture du parc, si c'est le cas on arr�te la simulation
			if (getHeure() == heureFin) {
				running = false;
			}

			// Attendre une minute simul�e pour la console
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		// D�tacher le thread de l'horloge pour qu'il s'ex�cute en arri�re-plan
		}).detach();
}

//Mettre l'horloge en pause
//Cette m�thode n'a pas vraiment �t� utilis�e dans le script final, il s'agissait plus d'un outil pour tester l'horloge et son fonctionnement
void Horloge::stop() {
	running = false;
}

//Fonction pour savoir si l'horloge tourne ou pas
bool Horloge::estEnCours() const {
	return running;
}

//Avance l'horloge d'une minute
void Horloge::avancerTemps() {
	// Avancer d'une minute
	tempsActuel += std::chrono::minutes(1);
}

//Getter pour avoir l'heure actuelle dans la simulation
int Horloge::getHeure() const {
	time_t time = std::chrono::system_clock::to_time_t(tempsActuel);
	struct tm timeinfo;
	localtime_s(&timeinfo, &time);
	return timeinfo.tm_hour;
}

//Getter pour avoir la minute actuelle dans la simulation
int Horloge::getMinute() const {
	time_t time = std::chrono::system_clock::to_time_t(tempsActuel);
	struct tm timeinfo;
	localtime_s(&timeinfo, &time);
	return timeinfo.tm_min;
}