#pragma once
#ifndef HORLOGE_H
#define HORLOGE_H

#include <chrono>

class Horloge {
public:
	Horloge();

	void avancerTemps(int heures);

	int getHeureActuelle() const;

private:
	std::chrono::system_clock::time_point heureActuelle;
};

#endif // HORLOGE_H
