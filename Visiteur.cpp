#include "Visiteur.h" // Inclure le fichier d'en-t�te de Visiteur avant tout autre fichier d'en-t�te
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
	// Impl�menter la logique de prise de d�cision
}

std::string Visiteur::GetNom() const {
	return Nom;
}

Visiteur::~Visiteur() {}