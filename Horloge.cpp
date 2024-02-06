#include "Horloge.h"
#include <iostream>
#include <thread>
#include <chrono>

Horloge::Horloge() {
	// Récupérer la date et l'heure actuelle du système
	std::time_t maintenant = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	// Convertir la date et l'heure actuelle en une structure tm (pour accéder aux informations sur l'heure)
	std::tm ltm;
	localtime_s(&ltm, &maintenant); // Utilisation de localtime_s au lieu de localtime

	// Initialiser l'heure de l'horloge à 00h00
	ltm.tm_hour = 0;
	ltm.tm_min = 0;
	ltm.tm_sec = 0;

	// Convertir la structure tm en time_t
	std::time_t debutDuJour = std::mktime(&ltm);

	// Convertir le time_t en un objet time_point
	heureActuelle = std::chrono::system_clock::from_time_t(debutDuJour);
}

void Horloge::avancerTemps(int heures) {
	heureActuelle += std::chrono::hours(heures);
}

int Horloge::getHeureActuelle() const {
	auto duree = heureActuelle.time_since_epoch();
	return std::chrono::duration_cast<std::chrono::hours>(duree).count() % 24;
}