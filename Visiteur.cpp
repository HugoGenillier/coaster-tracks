#include "Visiteur.h" // Inclure le fichier d'en-tête de Visiteur avant tout autre fichier d'en-tête
#include "Attraction.h"

Visiteur::Visiteur(std::string nom) : Nom(nom), TempsAttendu(0), Etat(EtatVisiteur::EnDecision), Position({ 0, 0 }) {}

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
	// Implémenter la logique de prise de décision
}

std::string Visiteur::GetNom() const {
	return Nom;
}

Visiteur::~Visiteur() {}