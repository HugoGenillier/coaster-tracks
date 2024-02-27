
#pragma once
#include <chrono>
#include <thread>

class Horloge {
public:
	Horloge(int heureDebut, int heureFin);
	void start();
	void stop();
	bool estEnCours() const;
	void avancerTemps();
	int getHeure() const;
	int getMinute() const;

private:
	std::chrono::system_clock::time_point tempsActuel;
	int heureDebut;
	int heureFin;
	bool running;
};
