#include "Horloge.h"
#include <iostream>
#include <thread>
#include <chrono>

Horloge::Horloge() : heureActuelle(std::chrono::system_clock::now()) {}

void Horloge::avancerTemps(int heures) {
	heureActuelle += std::chrono::hours(heures);
}

int Horloge::getHeureActuelle() const {
	auto duree = heureActuelle.time_since_epoch();
	return std::chrono::duration_cast<std::chrono::hours>(duree).count() % 24;
}