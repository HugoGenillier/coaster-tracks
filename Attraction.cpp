#include "Attraction.h"


// Constructeur de la classe Attraction
Attraction::Attraction(const std::string& nom, int capacite, int tempsFonctionnement)
	: Nom(nom), Capacite(capacite), TempsFonctionnementRestant(tempsFonctionnement), TempsTour(tempsFonctionnement) {}


// M�thode publique
void Attraction::AfficherDetails() const {
	int TempsAttenteActuel = TempsAttenteEstime();
	cout << "Nom : " << Nom << ", Capacite : " << Capacite << ", Temps d'attente actuel : " << TempsAttenteActuel << endl;
}

void Attraction::ReduireTempsFonctionnementRestant() {
	if (TempsFonctionnementRestant > 0) {
		TempsFonctionnementRestant--;
	}
}

void Attraction::RetirerVisiteursTermines() {
	// Tant que la file d'attente n'est pas vide et qu'il reste des places disponibles dans l'attraction
	while (!FileAttente.empty() && Capacite > 0) {
		// Retirer le visiteur en t�te de file
		FileAttente.pop();

		// D�cr�menter la capacit� de l'attraction
		Capacite--;
	}
}

void Attraction::AjouterVisiteur(const Visiteur& visiteur) {
	// Ajouter le visiteur � la file d'attente
	FileAttente.push(visiteur);
}

int Attraction::GetTempsFonctionnementRestant() const {
	return TempsFonctionnementRestant;
}

int Attraction::GetNombreVisiteur() const {
	return FileAttente.size();
}

int Attraction::TempsAttenteEstime() const {
	// Calculer le nombre de visiteurs dans la file d'attente
	int nombreVisiteurs = FileAttente.size();

	// Si la file d'attente est vide ou si la capacit� de l'attraction est nulle, le temps d'attente est de z�ro
	if (nombreVisiteurs == 0 || Capacite == 0) {
		return 0;
	}

	// Calculer le temps restant avant le prochain tour
	int tempsRestantAvantTour = GetTempsFonctionnementRestant();

	// Calculer le nombre de tours n�cessaires pour faire passer tous les visiteurs
	int nombreTours = (nombreVisiteurs + Capacite - 1) / Capacite; // Division enti�re arrondie par exc�s

	// Calculer le temps d'attente estim� en fonction du nombre de tours et du temps n�cessaire pour un tour
	int tempsAttente = tempsRestantAvantTour + (nombreTours - 1) * TempsTour;

	return tempsAttente;
}

void Attraction::AvancerTour() {
	// Si l'attraction est toujours en fonctionnement
	if (TempsFonctionnementRestant > 0) {
		// R�duire le temps restant avant le prochain tour
		--TempsFonctionnementRestant;

		// Si le temps restant avant le prochain tour est �coul�
		if (TempsFonctionnementRestant == 0) {
			// Faire embarquer un groupe de visiteurs depuis la file d'attente
			int visiteursAEmbarquer = std::min(static_cast<int>(FileAttente.size()), Capacite);
			for (int i = 0; i < visiteursAEmbarquer; ++i) {
				// Retirer le visiteur en t�te de file et simuler son passage dans l'attraction
				FileAttente.pop();
			}

			// R�initialiser le temps restant avant le prochain tour avec le temps de tour de l'attraction
			TempsFonctionnementRestant = TempsTour;
		}
	}
}
std::string Attraction::GetNom() const {
	return Nom; // Retourne le nom de l'attraction
}

// Destructeur
Attraction::~Attraction() {}