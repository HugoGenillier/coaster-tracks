#include "Visiteur.h" // Inclure le fichier d'en-t�te de Visiteur avant tout autre fichier d'en-t�te
#include "Attraction.h"

Visiteur::Visiteur(std::string nom, std::vector<Attraction>& attractions) {
	Nom = nom;
	TempsAttendu = 0;
	Etat = EtatVisiteur::EnDecision;
	Position = { 0, 0 };

	// Initialiser ListeAttractions avec toutes les attractions et marquer chaque attraction comme non visit�e et non favorite
	for (auto& attraction : attractions) {
		ListeAttractions.push_back(std::make_tuple(&attraction, false, false));
	}

	// Choisir trois attractions au hasard et les marquer comme favorites
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<size_t> dist(0, ListeAttractions.size() - 1);

	for (int i = 0; i < 3; ++i) {
		size_t randomIndex = dist(gen);
		std::get<2>(ListeAttractions[randomIndex]) = true;
	}
}

Visiteur::Visiteur() {}

void Visiteur::AfficherDetails() const {
	std::cout << "Nom : " << Nom << ", Temps total d'attente : " << TempsAttendu << std::endl;
}

void Visiteur::ActiverVisiteur() {
	switch (Etat) {
	case EtatVisiteur::EnDecision:
		//std::cout << "Visiteur " << Nom << " est en train de faire une d�cision" << std::endl;
		FaireDecision();
		break;
	case EtatVisiteur::EnMarche:
		//std::cout << "Visiteur " << Nom << " va vers " << Objectif->GetNom() << " position : " << GetPosition().x << ", " << GetPosition().y << std::endl;
		DeplacerVersAttraction();
		break;
	case EtatVisiteur::EnFileAttente:
		//std::cout << "Visiteur " << Nom << " est en file d'attente" << std::endl;
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

	for (auto& attractionTuple : ListeAttractions) {
		Attraction* attraction = std::get<0>(attractionTuple);
		bool estDejaVisitee = std::get<1>(attractionTuple);
		bool estFavorite = std::get<2>(attractionTuple); // Ajout de cette fonction pour v�rifier si l'attraction est favorite

		if (!estDejaVisitee) { // V�rifier si l'attraction n'a pas encore �t� visit�e
			// Calculer le score d'attractivit� de cette attraction
			double score = 0.0;

			// Calculer la distance entre le visiteur et l'attraction
			double distance = std::sqrt(std::pow(Position.x - attraction->GetPosition().x, 2) +
				std::pow(Position.y - attraction->GetPosition().y, 2));

			// Si la distance est nulle, cela signifie que le visiteur est d�j� � l'attraction
			if (distance == 0) {
				score = std::numeric_limits<double>::infinity(); // Affecter une valeur infinie au score
			}
			else {
				// Calculer le score bas� sur la distance et le temps d'attente actuel
				if (attraction->TempsAttenteEstime() != 0) {
					score = 1 / distance * (1 / (5 * attraction->TempsAttenteEstime()));
				}
				else {
					// Si le temps d'attente estim� est nul, affecter une valeur tr�s basse au score
					score = std::numeric_limits<double>::max();
				}
			}

			// Appliquer un poids suppl�mentaire si l'attraction est favorite
			if (estFavorite) {
				score+=1/1000;
				score *= 10;
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

void Visiteur::AjouterAttractionVisitee(Attraction* attraction) {
	// Parcourir le vecteur des attractions du visiteur
	for (auto& attractionTuple : ListeAttractions) {
		// Si l'attraction correspond � celle visit�e
		if (std::get<0>(attractionTuple) == attraction) {
			// Mettre � jour le bool�en associ� � cette attraction
			std::get<1>(attractionTuple) = true;
			break; // Sortir de la boucle une fois que l'attraction a �t� trouv�e
		}
	}
}

void Visiteur::ChangerComportement(EtatVisiteur nouvelEtat) {
	Etat = nouvelEtat;
}

std::string Visiteur::GetNom() const {
	return Nom;
}

Visiteur::~Visiteur() {}