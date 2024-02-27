#include "main.h"
#include "Parc.h"
#include "Horloge.h"

int main() {
	// Créer une instance de Parc sans attractions
	Parc parc({}); // Passer un vecteur vide d'attractions

	// Simuler une journée dans le parc de 9h à 18h
	parc.simulerJournee(9, 10);

	return 0;
}