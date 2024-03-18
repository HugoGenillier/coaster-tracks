#include "Visiteur.h" // Inclure le fichier d'en-tête de Visiteur avant tout autre fichier d'en-tête
#include "Attraction.h"


Visiteur::Visiteur(std::string nom, std::vector<Attraction>& attractions)
{
	Nom = nom;
	TempsAttendu = 0;
	Etat = EtatVisiteur::EnDecision;
	Position = { 0, 0 };
	for (auto& attraction : attractions) {
		this->ListeAttractions.push_back(std::make_pair(&attraction, false)); // Utiliser un pointeur vers l'attraction
	}
}

Visiteur::Visiteur() {}

void Visiteur::AfficherDetails() const {
	std::cout << "Nom : " << Nom << ", Temps total d'attente : " << TempsAttendu << std::endl;
}

void Visiteur::ActiverVisiteur() {
	switch (Etat) {
	case EtatVisiteur::EnDecision:
		FaireDecision();
		break;
	case EtatVisiteur::EnMarche:
		DeplacerVersAttraction();
		break;
	case EtatVisiteur::EnFileAttente:
		TempsAttendu += 1; // Incrémenter le temps d'attente du visiteur
		break;
	default:
		// Gérer d'autres états si nécessaire
		break;
	}
}

void Visiteur::DeplacerVersAttraction() {

	// Vérifier si le visiteur est déjà à l'emplacement de l'attraction
	if (Position == Objectif->GetPosition()) {
		// Le visiteur est arrivé à l'attraction, changer son état en EnFileAttente
		Etat = EtatVisiteur::EnFileAttente;
		// Ajouter le visiteur à la file d'attente de l'attraction
		Objectif->AjouterVisiteur(this); // Assurez-vous que Objectif est un pointeur
	}
	else {
		// Calculer le déplacement vers l'attraction
		// Pour simplifier, vous pouvez implémenter un déplacement linéaire
		double deltaX = Objectif->GetPosition().x - Position.x;
		double deltaY = Objectif->GetPosition().y - Position.y;

		// Calculer le déplacement horizontal et vertical
		double deplacementX = (deltaX != 0) ? deltaX / abs(deltaX) : 0.0;
		double deplacementY = (deltaY != 0) ? deltaY / abs(deltaY) : 0.0;

		// Mettre à jour la position du visiteur
		Position.x += deplacementX;
		Position.y += deplacementY;
	}
}

void Visiteur::FaireDecision() {
	// Déterminer l'attraction la plus attrayante non visitée
	Attraction* meilleureAttraction = nullptr;
	double meilleurScore = -1; // Initialiser à un score très bas

	for (auto& attractionPair : ListeAttractions) {
		Attraction* attraction = attractionPair.first;
		if (!attractionPair.second) { // Vérifier si l'attraction n'a pas encore été visitée
			// Calculer le score d'attractivité de cette attraction
			double score = 0.0;

			// Calculer la distance entre le visiteur et l'attraction
			double distance = std::sqrt(std::pow(Position.x - attraction->GetPosition().x, 2) +
				std::pow(Position.y - attraction->GetPosition().y, 2));

			// Si la distance est nulle, cela signifie que le visiteur est déjà à l'attraction
			// Dans ce cas, on évite de diviser par zéro et on assigne un score très bas
			if (distance == 0) {
				score = -1;
			}
			else {
				// Calculer le score basé sur la distance et le temps d'attente actuel
				score = 1 / distance * (1 / attraction->TempsAttenteEstime());
			}

			// Si le score est plus élevé que le meilleur score actuel, mettre à jour l'attraction choisie
			if (score > meilleurScore) {
				meilleureAttraction = attraction;
				meilleurScore = score;
			}
		}
	}

	// Si une attraction a été trouvée, mettre à jour l'objectif du visiteur
	if (meilleureAttraction != nullptr) {
		Objectif = meilleureAttraction;
		Etat = EtatVisiteur::EnMarche; // Changer l'état en EnMarche pour se déplacer vers la meilleure attraction
	}
}

std::string Visiteur::GetNom() const {
	return Nom;
}

Visiteur::~Visiteur() {}