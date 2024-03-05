#include "Attraction.h"


// Constructeur de la classe Attraction
Attraction::Attraction(const std::string& nom, int capacite, int tempsFonctionnement)
	: Nom(nom), Capacite(capacite), TempsFonctionnementRestant(tempsFonctionnement), TempsTour(tempsFonctionnement) {}


// Méthode publique
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
		// Retirer le visiteur en tête de file
		FileAttente.pop();

		// Décrémenter la capacité de l'attraction
		Capacite--;
	}
}

void Attraction::AjouterVisiteur(const Visiteur& visiteur) {
	// Ajouter le visiteur à la file d'attente
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

	// Vérifier si la file d'attente est vide ou si la capacité de l'attraction est nulle
	if (nombreVisiteurs == 0 || Capacite == 0) {
		return 0; // Pas d'attente si la file est vide ou si la capacité est nulle
	}

	// Calculer le temps d'attente estimé en fonction du nombre de visiteurs dans la file, de la capacité et du temps d'un tour
	int tempsAttente = (nombreVisiteurs / Capacite) * TempsTour;
	return tempsAttente;
}

void Attraction::AvancerTour() {
	// Si l'attraction est toujours en fonctionnement
	if (!FileAttente.empty()) {
		// Calculer le nombre de visiteurs à faire embarquer pour ce tour
		size_t visiteursAEmbarquer = std::min(FileAttente.size(), static_cast<size_t>(Capacite));


		// Faire embarquer les visiteurs par groupes
		for (int i = 0; i < visiteursAEmbarquer; ++i) {
			// Retirer le visiteur en tête de file
			Visiteur visiteur = FileAttente.front();
			FileAttente.pop();

			// Faire passer le visiteur à travers l'attraction (simulation)
			// Ici vous pouvez placer la logique de traitement du visiteur dans l'attraction
			// par exemple, mettre à jour les statistiques du visiteur, etc.
		}

		// Mettre à jour le temps restant de l'attraction après chaque tour effectué
		ReduireTempsFonctionnementRestant();
	}
}
std::string Attraction::GetNom() const {
	return Nom; // Retourne le nom de l'attraction
}

// Destructeur
Attraction::~Attraction() {}
