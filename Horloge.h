#pragma once
#ifndef HORLOGE_H
#define HORLOGE_H

#include <chrono>
#include <iostream>
#include <thread>
#include <ctime> // Pour localtime_s

class Horloge {
public:
	Horloge(int heureDebut, int heureFin); // Constructeur avec heure de début et heure de fin
	void start(); // Méthode pour démarrer la simulation du temps
	void stop(); // Méthode pour arrêter la simulation du temps
	void avancerTemps(); // Méthode pour avancer l'heure dans l'horloge
	int getHeure() const; // Méthode pour obtenir l'heure actuelle de l'horloge
	int getMinute() const; // Méthode pour obtenir la minute actuelle de l'horloge


private:
	std::chrono::time_point<std::chrono::system_clock> tempsActuel; // Temps actuel de l'horloge
	bool running; // Indicateur pour indiquer si la simulation du temps est en cours
	int heureDebut; // Heure de début de la simulation
	int heureFin; // Heure de fin de la simulation
};
#endif // HORLOGE_H
