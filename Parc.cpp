#include "Parc.h"
#include <iomanip> // Inclure la biblioth�que iomanip pour utiliser setw

// Constructeur
Parc::Parc(std::string nom) : Nom(nom), Attractions(), Visiteurs() {}


// M�thode publique
void Parc::AfficherDetails() const {
	cout << "Nom : " << Nom << endl;
}


void Parc::AjouterAttraction(const Attraction& attraction) {
	Attractions.push_back(attraction); // Ajoute l'attraction � la liste des attractions du parc
}


void Parc::simulerJournee(int heureOuverture, int heureFermeture, sf::RenderWindow& window) {
    std::cout << "Simulation de la journ�e dans le parc de " << heureOuverture << "h � " << heureFermeture << "h\n";

    // Cr�ation de l'horloge au moment du d�marrage de la simulation de la journ�e
    Horloge horloge(heureOuverture, heureFermeture);
    horloge.start();

    // Charger la police pour afficher le texte
    sf::Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        // Gestion de l'erreur si le chargement de la police a �chou�
        std::cerr << "Erreur : impossible de charger la police arial.ttf." << std::endl;
        return;
    }

    // Espacement vertical initial pour les textes des attractions
    float verticalSpacing = 50.0f;

    // Boucle de rendu SFML pour afficher � chaque �tape de la simulation
    while (horloge.estEnCours()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer la fen�tre avant de dessiner
        window.clear();

        // R�cup�rer l'heure actuelle de l'horloge
        int heure = horloge.getHeure();
        int minute = horloge.getMinute();

        // Cr�er un texte pour afficher l'heure
        sf::Text timeText("Heure : " + std::to_string(heure) + "h" + std::to_string(minute), font, 24);
        timeText.setPosition(10, 10); // Position du texte dans la fen�tre

        // Dessiner le texte de l'heure
        window.draw(timeText);

        // Dessiner l'�tat de chaque attraction
        for (auto& attraction : Attractions) {
            attraction.AvancerTour(); // Faire avancer la file d'attente et le temps d'attente estim� de l'attraction

            // Cr�er un texte pour afficher l'�tat de l'attraction
            sf::Text attractionText("Attraction : " + attraction.GetNom() + " | " + std::to_string(attraction.TempsAttenteEstime()) + " minutes", font, 18);
            attractionText.setPosition(10, verticalSpacing); // Position du texte dans la fen�tre
            window.draw(attractionText);

            // Augmenter l'espacement vertical pour le texte de la prochaine attraction
            verticalSpacing += 30.0f;
        }

        // R�initialiser l'espacement vertical pour le prochain tour de boucle
        verticalSpacing = 50.0f;

        // Activer les visiteurs
        for (auto& visiteur : Visiteurs) {
            visiteur.ActiverVisiteur(); // Activer le visiteur
        }

        // Mettre � jour l'affichage
        window.display();

        // Attendre une seconde (simulation de l'heure)
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Attendre 1 seconde pour simuler une minute
    }

    std::cout << "Fin de la journ�e dans le parc\n";
}


void Parc::Lib�rerVisiteurs() {
	for (Attraction& attraction : Attractions) {
		std::queue<Visiteur*>& fileAttente = attraction.GetFileAttente();
		while (!fileAttente.empty()) {
			Visiteur* visiteur = fileAttente.front();
			delete visiteur; // Lib�rer la m�moire allou�e pour chaque visiteur
			fileAttente.pop();
		}
	}
}


// Destructeur
Parc::~Parc() {}