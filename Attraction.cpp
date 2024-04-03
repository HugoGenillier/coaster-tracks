#include "Attraction.h"
#include "Visiteur.h"

//Constructeur d'attractions
Attraction::Attraction(const std::string& nom, int capacite, int tempsFonctionnement, Coordonnees position)
	: Nom(nom), Capacite(capacite), TempsFonctionnementRestant(tempsFonctionnement), TempsTour(tempsFonctionnement), Position(position) {}

Attraction::Attraction() {}

//Méthode pour avoir les détails de l'attraction, cette méthode était utilisée lorsque l'affichage était encore uniquement via la console.
void Attraction::AfficherDetails() const {
	int TempsAttenteActuel = TempsAttenteEstime();
	std::cout << "Nom : " << Nom << ", Capacite : " << Capacite << ", Temps d'attente actuel : " << TempsAttenteActuel << std::endl;
}

//Méthode pour retirer les visiteurs qui viennent de faire l'attraction
void Attraction::RetirerVisiteursTermines() {
	while (!FileAttente.empty() && Capacite > 0) {
		FileAttente.pop();
		Capacite--;
	}
}

//Ajouter un visiteur dans la file d'attente de l'attraction
void Attraction::AjouterVisiteur(Visiteur* visiteur) {
	FileAttente.push(visiteur);
}

//Getter pour obtenir le temps qu'il reste avant que le tour ne soit fini
int Attraction::GetTempsFonctionnementRestant() const {
	return TempsFonctionnementRestant;
}

//Getter pour obtenir le nombre de personnes dans la file d'attente
int Attraction::GetNombreVisiteur() const {
	return FileAttente.size();
}

//Getter pour avoir la position de l'attraction
const Coordonnees& Attraction::GetPosition() const { return Position; }

//Méthode d'estimation du temps d'attente dans l'attraction en connaissant le nombre de personne en file d'attente et les caractéristiques de l'attraction
int Attraction::TempsAttenteEstime() const {
	int nombreVisiteurs = FileAttente.size();
	// Si la file d'attente est vide ou si la capacité de l'attraction est nulle, le temps d'attente est de zéro
	if (nombreVisiteurs == 0 || Capacite == 0) {
		return 0;
	}

	// Calcul du temps restant avant le prochain tour
	int tempsRestantAvantTour = GetTempsFonctionnementRestant();
	// Calcul du nombre de tours nécessaires pour faire passer tous les visiteurs de la file
	int nombreTours = (nombreVisiteurs + Capacite - 1) / Capacite;

	// Calculer le temps d'attente estimé en fonction du nombre de tours à faire pour écouler toute la file et du temps nécessaire pour un tour
	int tempsAttente = tempsRestantAvantTour + (nombreTours - 1) * TempsTour;

	return tempsAttente;
}

//Méthode pour faire avancer la simulation au niveau des attractions, donc faire fonctionner les attractions, avancer les files d'attentes et estimer le temps d'attente
void Attraction::AvancerTour() {

	//Si l'attraction est en train de tourner (en plein dans un tour de fonctionnement)
	if (TempsFonctionnementRestant > 0) {
		// Réduire le temps restant avant le prochain tour
		--TempsFonctionnementRestant;

		// Si le temps restant avant le prochain tour est écoulé
		if (TempsFonctionnementRestant == 0) {

			// On fait embarquer un groupe de visiteurs depuis la file d'attente
			std::queue<Visiteur*> fileAttenteNonConst = FileAttente;
			int visiteursAEmbarquer = std::min(static_cast<int>(fileAttenteNonConst.size()), Capacite);
			for (int i = 0; i < visiteursAEmbarquer; ++i) {
				// Retirer le visiteur en tête de file
				Visiteur* visiteur = fileAttenteNonConst.front();
				fileAttenteNonConst.pop();
				// Mettre à jour l'attraction visitée par le visiteur
				visiteur->AjouterAttractionVisitee(this);
				// Changer le comportement du visiteur de l'état d'attente à l'état de prise de décision
				visiteur->ChangerComportement(EtatVisiteur::EnDecision);
			}
			FileAttente = fileAttenteNonConst;

			// Réinitialiser le temps restant avant le prochain tour avec le temps de fonctionnement de l'attraction
			TempsFonctionnementRestant = TempsTour;
		}
	}
}

//Getter pour le nom de l'attraction
std::string Attraction::GetNom() const {
	return Nom; // Retourne le nom de l'attraction
}

//Getter pour avoir la file d'attente de l'attraction
std::queue<Visiteur*>& Attraction::GetFileAttente() {
	return FileAttente;
}

// Destructeur
Attraction::~Attraction() {}