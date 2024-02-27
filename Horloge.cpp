#include "Horloge.h"
#pragma once
#include <chrono>

#include "Horloge.h"

Horloge::Horloge(int heureDebut, int heureFin) : heureDebut(heureDebut), heureFin(heureFin), running(false) {
	// Initialiser l'horloge � l'heure de d�but fixe
	tempsActuel = std::chrono::system_clock::time_point{}; // D�but de l'epoch
	tempsActuel += std::chrono::hours(heureDebut - 1);
}

void Horloge::start() {
	running = true;
	std::thread([this]() {
		while (running) {
			// Avancer d'une minute
			avancerTemps();

			// V�rifier si l'heure actuelle est �gale � l'heure de fin
			if (getHeure() == heureFin) {
				// Si c'est le cas, arr�ter la simulation
				running = false;
			}

			// Attendre une minute simul�e
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		}).detach(); // D�tacher le thread pour qu'il s'ex�cute en arri�re-plan
}

void Horloge::stop() {
	running = false;
}

bool Horloge::estEnCours() const {
	return running;
}

void Horloge::avancerTemps() {
	// Avancer d'une minute
	tempsActuel += std::chrono::minutes(1);
}

int Horloge::getHeure() const {
	// Extraire l'heure actuelle � partir du temps actuel en utilisant localtime_s
	time_t time = std::chrono::system_clock::to_time_t(tempsActuel);
	struct tm timeinfo;
	localtime_s(&timeinfo, &time);
	return timeinfo.tm_hour;
}

int Horloge::getMinute() const {
	// Extraire les minutes actuelles � partir du temps actuel en utilisant localtime_s
	time_t time = std::chrono::system_clock::to_time_t(tempsActuel);
	struct tm timeinfo;
	localtime_s(&timeinfo, &time);
	return timeinfo.tm_min;
}