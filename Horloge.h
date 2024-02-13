#pragma once
#ifndef HORLOGE_H
#define HORLOGE_H

#include <chrono>
#include <iostream>
#include <thread>
#include <ctime> // Pour localtime_s

class Horloge {
public:
	Horloge(int heureDebut, int heureFin); // Constructeur avec heure de d�but et heure de fin
	void start(); // M�thode pour d�marrer la simulation du temps
	void stop(); // M�thode pour arr�ter la simulation du temps
	void avancerTemps(); // M�thode pour avancer l'heure dans l'horloge
	int getHeure() const; // M�thode pour obtenir l'heure actuelle de l'horloge
	int getMinute() const; // M�thode pour obtenir la minute actuelle de l'horloge


private:
	std::chrono::time_point<std::chrono::system_clock> tempsActuel; // Temps actuel de l'horloge
	bool running; // Indicateur pour indiquer si la simulation du temps est en cours
	int heureDebut; // Heure de d�but de la simulation
	int heureFin; // Heure de fin de la simulation
};
#endif // HORLOGE_H
