#include "Visiteur.h" // Inclure le fichier d'en-t�te de Visiteur avant tout autre fichier d'en-t�te
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
		TempsAttendu += 1; // Incr�menter le temps d'attente du visiteur
		break;
	default:
		// G�rer d'autres �tats si n�cessaire
		break;
	}
}

void Visiteur::DeplacerVersAttraction() {

	// V�rifier si le visiteur est d�j� � l'emplacement de l'attraction
	if (Position == Objectif->GetPosition()) {
		// Le visiteur est arriv� � l'attraction, changer son �tat en EnFileAttente
		Etat = EtatVisiteur::EnFileAttente;
		// Ajouter le visiteur � la file d'attente de l'attraction
		Objectif->AjouterVisiteur(this); // Assurez-vous que Objectif est un pointeur
	}
	else {
		// Calculer le d�placement vers l'attraction
		// Pour simplifier, vous pouvez impl�menter un d�placement lin�aire
		double deltaX = Objectif->GetPosition().x - Position.x;
		double deltaY = Objectif->GetPosition().y - Position.y;

		// Calculer le d�placement horizontal et vertical
		double deplacementX = (deltaX != 0) ? deltaX / abs(deltaX) : 0.0;
		double deplacementY = (deltaY != 0) ? deltaY / abs(deltaY) : 0.0;

		// Mettre � jour la position du visiteur
		Position.x += deplacementX;
		Position.y += deplacementY;
	}
}

void Visiteur::FaireDecision() {
	// D�terminer l'attraction la plus attrayante non visit�e
	Attraction* meilleureAttraction = nullptr;
	double meilleurScore = -1; // Initialiser � un score tr�s bas

	for (auto& attractionPair : ListeAttractions) {
		Attraction* attraction = attractionPair.first;
		if (!attractionPair.second) { // V�rifier si l'attraction n'a pas encore �t� visit�e
			// Calculer le score d'attractivit� de cette attraction
			double score = 0.0;

			// Calculer la distance entre le visiteur et l'attraction
			double distance = std::sqrt(std::pow(Position.x - attraction->GetPosition().x, 2) +
				std::pow(Position.y - attraction->GetPosition().y, 2));

			// Si la distance est nulle, cela signifie que le visiteur est d�j� � l'attraction
			// Dans ce cas, on �vite de diviser par z�ro et on assigne un score tr�s bas
			if (distance == 0) {
				score = -1;
			}
			else {
				// Calculer le score bas� sur la distance et le temps d'attente actuel
				score = 1 / distance * (1 / attraction->TempsAttenteEstime());
			}

			// Si le score est plus �lev� que le meilleur score actuel, mettre � jour l'attraction choisie
			if (score > meilleurScore) {
				meilleureAttraction = attraction;
				meilleurScore = score;
			}
		}
	}

	// Si une attraction a �t� trouv�e, mettre � jour l'objectif du visiteur
	if (meilleureAttraction != nullptr) {
		Objectif = meilleureAttraction;
		Etat = EtatVisiteur::EnMarche; // Changer l'�tat en EnMarche pour se d�placer vers la meilleure attraction
	}
}

std::string Visiteur::GetNom() const {
	return Nom;
}

Visiteur::~Visiteur() {}