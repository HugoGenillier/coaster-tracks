#include "Visiteur.h"
#include "Attraction.h"

Visiteur::Visiteur(std::string nom, std::vector<Attraction>& attractions) {
	Nom = nom;
	TempsAttendu = 0;
	Etat = EtatVisiteur::EnDecision;
	Position = { 0, 0 };

	// Initialiser ListeAttractions avec toutes les attractions et marquer chaque attraction comme non visitée et non favorite
	for (auto& attraction : attractions) {
		ListeAttractions.push_back(std::make_tuple(&attraction, false, false));
	}

	// Prend trois attractions au hasard et les marquer comme favorites
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<size_t> dist(0, ListeAttractions.size() - 1);

	for (int i = 0; i < 3; ++i) {
		size_t randomIndex = dist(gen);
		std::get<2>(ListeAttractions[randomIndex]) = true;
	}
}

Visiteur::Visiteur() {}

//Méthode qui affiche le détail d'un visiteur avec son nom et le temps d'attente total qu'il à passé dans le parc
void Visiteur::AfficherDetails() const {
	std::cout << "Nom : " << Nom << ", Temps total d'attente : " << TempsAttendu << std::endl;
}

//Méthode qui active le visiteur lors d'une itération de la boucle, ce dernier soit marche, soit prend une décision, soit attend.
void Visiteur::ActiverVisiteur() {
	switch (Etat) {
		//Prise de décision
	case EtatVisiteur::EnDecision:
		FaireDecision();
		break;
		//Marcher vers une attraction
	case EtatVisiteur::EnMarche:
		DeplacerVersAttraction();
		break;
		//Attendre (ne rien faire) et ajouter une minute au temps total attendu
	case EtatVisiteur::EnFileAttente:
		TempsAttendu += 1;
		break;
	default:

		break;
	}
}

void Visiteur::DeplacerVersAttraction() {
	// Vérifie si le visiteur est arrivé à son objectif
	if (Position == Objectif->GetPosition()) {
		// Faire rentrer le visiteur dans la file d'attente de l'attraction 
		Etat = EtatVisiteur::EnFileAttente;
		Objectif->AjouterVisiteur(this);
	}
	else {
		// Calculer le déplacement vers l'attraction (distance euclidienne)
		double deltaX = Objectif->GetPosition().x - Position.x;
		double deltaY = Objectif->GetPosition().y - Position.y;

		//Faire avancer le visiteur droit vers son attraction
		//Ici il faut faire attention de garder à l'esprit qu'un visiteur fait un déplacement pendant une itération de boucle
		//donc pendant 1 minutes simulée ! un déplacement strictement horizontal ou vertical de une unité se fait en 1 itération complète.
		double deplacementX = (deltaX != 0) ? deltaX / abs(deltaX) : 0.0;
		double deplacementY = (deltaY != 0) ? deltaY / abs(deltaY) : 0.0;
		Position.x += deplacementX;
		Position.y += deplacementY;
	}
}

//Méthode de prise de décision du visiteur. Il effectue un choix parmis toutes les attractions disponibles en prenant en compte la distance, le temps
//ses favoris et si il a déjà fait l'attraction ou non.
void Visiteur::FaireDecision() {

	Attraction* meilleureAttraction = nullptr;
	double meilleurScore = -1;

	//Pour chaques attractions du parc
	for (auto& attractionTuple : ListeAttractions) {
		Attraction* attraction = std::get<0>(attractionTuple);
		bool estDejaVisitee = std::get<1>(attractionTuple);
		bool estFavorite = std::get<2>(attractionTuple);

		//Si l'attraction à déjà été visitée, le visiteur n'y retournera pas.
		if (!estDejaVisitee) { 
			double score = 0.0;

			// Calcul de la distance entre le visiteur et l'attraction (euclidienne)
			double distance = std::sqrt(std::pow(Position.x - attraction->GetPosition().x, 2) +
				std::pow(Position.y - attraction->GetPosition().y, 2));

			// Cas ou la distance est nulle : le visiteur est déjà à l'attraction
			if (distance == 0) {
				score = std::numeric_limits<double>::infinity();
			}


			else {
				// Calculer le score basé sur la distance et le temps d'attente actuel de l'attraction
				//La pondération est que le temps d'attente est 8 fois plus important que la distance.
				//Le paramètre n'est peu être pas le plus optimal, il faudrait une étude mathématique sur une modélisation
				// de choix plus poussée pour équilibrer.
				if (attraction->TempsAttenteEstime() != 0) {
					score = 1 / distance * (1 / (8 * attraction->TempsAttenteEstime()));
				}
				else {
					// Si le temps d'attente estimé est nul
					score = std::numeric_limits<double>::max();
				}
			}

			// Appliquer un poids supplémentaire au score de décision si l'attraction est favorite
			if (estFavorite) {
				//Score présent même si il n'y a aucune attente partout dans le parc, le visiteur est toujours attiré par ce qu'il aime.
				score+=1/1000;
				//Le score est multiplié par 10, là encore il faudrait se pencher plus sur la modélisation d'un comportement humain.
				score *= 10;
			}

			//Choix de la meilleure attraction, celle qui sera le choix du visiteur
			if (score > meilleurScore) {
				meilleureAttraction = attraction;
				meilleurScore = score;
			}
		}
	}

	//Mettre à jour l'objectif du visiteur
	if (meilleureAttraction != nullptr) {
		Objectif = meilleureAttraction;
		//Le visiteur se met alors en marche pour la prochane itération
		Etat = EtatVisiteur::EnMarche;
	}
}

//Méthode de modification des status des attractions pour les rendre comme visitée une fois faites
void Visiteur::AjouterAttractionVisitee(Attraction* attraction) {
	for (auto& attractionTuple : ListeAttractions) {
		if (std::get<0>(attractionTuple) == attraction) {
			std::get<1>(attractionTuple) = true;
			break;
		}
	}
}

//Méthode pour modifier l'état du visiteur
void Visiteur::ChangerComportement(EtatVisiteur nouvelEtat) {
	Etat = nouvelEtat;
}

//Getter pour le nom
std::string Visiteur::GetNom() const {
	return Nom;
}

//Getter pour savoir ce que fait le visiteur en ce moment
std::string Visiteur::GetActions() const {
	std::string actions;

	switch (Etat) {
	case EtatVisiteur::EnDecision:
		actions = "En train de faire une décision";
		break;
	case EtatVisiteur::EnMarche:
		actions = "En marche vers l'attraction : " + Objectif->GetNom();
		break;
	case EtatVisiteur::EnFileAttente:
		actions = "En file d'attente à l'attraction : " + Objectif->GetNom();
		break;
	default:
		actions = "État inconnu";
		break;
	}

	return actions;
}

Visiteur::~Visiteur() {}