#include "main.h"
#include "Parc.h"
#include "Horloge.h"

int main() {
	// Cr�er une instance de Parc sans attractions
	Parc parc({}); // Passer un vecteur vide d'attractions

	// Simuler une journ�e dans le parc de 9h � 18h
	parc.simulerJournee(9, 10);

	return 0;
}