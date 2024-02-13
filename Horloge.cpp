#include "Horloge.h"
#pragma once
#include <chrono>

Horloge::Horloge(int heureDebut, int heureFin) : heureDebut(heureDebut), heureFin(heureFin), running(false) {
	// Initialiser l'horloge � l'heure de d�but
	tempsActuel = std::chrono::system_clock::time_point{}; // D�but de l'epoch
	tempsActuel += std::chrono::hours(heureDebut);
}

void Horloge::start() {
	running = true;
	std::thread([this]() {
		while (running) {
			std::this_thread::sleep_for(std::chrono::seconds(1)); // Faire dormir le thread pendant une minute
			avancerTemps(); // Avancer d'une minute
		}
		}).detach(); // D�tacher le thread pour qu'il s'ex�cute en arri�re-plan
}

void Horloge::stop() {
	running = false;
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