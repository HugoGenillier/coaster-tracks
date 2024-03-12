#include "Visiteur.h"

// Constructeur
Visiteur::Visiteur(std::string nom) {
	Nom = nom;
	TempsAttendu = 0;
	EtatVisiteur::EnDecision;
	Position.x = 0;
	Position.y = 0;
}

// M�thode publique
void Visiteur::AfficherDetails() const {
	cout << "Nom : " << Nom << ", Temps total d'attente : " << TempsAttendu << endl;
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
		TempsAttendu += 1;
		// Ne rien faire, car le visiteur est en file d'attente
		break;
	default:
		// G�rer d'autres �tats si n�cessaire
		break;
	}
}

void Visiteur::DeplacerVersAttraction() {
	// V�rifier si le visiteur est d�j� � l'emplacement de l'attraction
	if (Position == Objectif.GetPosition()) {
		// Le visiteur est arriv� � l'attraction, changer son �tat en EnFileAttente
		Etat = EtatVisiteur::EnFileAttente;
		// Ajouter le visiteur � la file d'attente de l'attraction
		Objectif.AjouterVisiteur(*this); // Assurez-vous que Objectif est une r�f�rence � l'attraction
	}
	else {
		// Calculer le d�placement vers l'attraction
		// Pour simplifier, vous pouvez impl�menter un d�placement lin�aire
		double deltaX = Objectif.GetPosition().x - Position.x;
		double deltaY = Objectif.GetPosition().y - Position.y;

		// Calculer le d�placement horizontal et vertical
		double deplacementX = (deltaX != 0) ? deltaX / abs(deltaX) : 0.0;
		double deplacementY = (deltaY != 0) ? deltaY / abs(deltaY) : 0.0;

		// Mettre � jour la position du visiteur
		Position.x += deplacementX;
		Position.y += deplacementY;
	}
}

void Visiteur::FaireDecision() {

}

std::string Visiteur::GetNom() const {
	return Nom;
}

// Destructeur
Visiteur::~Visiteur() {}


