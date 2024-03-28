#include "Parc.h"
#include <iomanip> // Inclure la bibliothèque iomanip pour utiliser setw

// Constructeur
Parc::Parc(std::string nom) : Nom(nom), Attractions(), Visiteurs() {}


// Méthode publique
void Parc::AfficherDetails() const {
	cout << "Nom : " << Nom << endl;
}


void Parc::AjouterAttraction(const Attraction& attraction) {
	Attractions.push_back(attraction); // Ajoute l'attraction à la liste des attractions du parc
}


void Parc::simulerJournee(int heureOuverture, int heureFermeture, sf::RenderWindow& window) {
    std::cout << "Simulation de la journée dans le parc de " << heureOuverture << "h à " << heureFermeture << "h\n";

    // Création de l'horloge au moment du démarrage de la simulation de la journée
    Horloge horloge(heureOuverture, heureFermeture);
    horloge.start();

    // Charger la police pour afficher le texte
    sf::Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        // Gestion de l'erreur si le chargement de la police a échoué
        std::cerr << "Erreur : impossible de charger la police arial.ttf." << std::endl;
        return;
    }

    // Espacement vertical initial pour les textes des attractions
    float verticalSpacing = 50.0f;

    // Boucle de rendu SFML pour afficher à chaque étape de la simulation
    while (horloge.estEnCours()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer la fenêtre avant de dessiner
        window.clear();

        // Récupérer l'heure actuelle de l'horloge
        int heure = horloge.getHeure();
        int minute = horloge.getMinute();

        // Créer un texte pour afficher l'heure
        sf::Text timeText("Heure : " + std::to_string(heure) + "h" + std::to_string(minute), font, 24);
        timeText.setPosition(10, 10); // Position du texte dans la fenêtre

        // Dessiner le texte de l'heure
        window.draw(timeText);

        // Dessiner l'état de chaque attraction
        for (auto& attraction : Attractions) {
            attraction.AvancerTour(); // Faire avancer la file d'attente et le temps d'attente estimé de l'attraction

            // Créer un texte pour afficher l'état de l'attraction
            sf::Text attractionText("Attraction : " + attraction.GetNom() + " | " + std::to_string(attraction.TempsAttenteEstime()) + " minutes", font, 18);
            attractionText.setPosition(10, verticalSpacing); // Position du texte dans la fenêtre
            window.draw(attractionText);

            // Augmenter l'espacement vertical pour le texte de la prochaine attraction
            verticalSpacing += 30.0f;
        }

        // Réinitialiser l'espacement vertical pour le prochain tour de boucle
        verticalSpacing = 50.0f;

        // Activer les visiteurs
        for (auto& visiteur : Visiteurs) {
            visiteur.ActiverVisiteur(); // Activer le visiteur
        }

        // Mettre à jour l'affichage
        window.display();

        // Attendre une seconde (simulation de l'heure)
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Attendre 1 seconde pour simuler une minute
    }

    std::cout << "Fin de la journée dans le parc\n";
}


void Parc::LibérerVisiteurs() {
	for (Attraction& attraction : Attractions) {
		std::queue<Visiteur*>& fileAttente = attraction.GetFileAttente();
		while (!fileAttente.empty()) {
			Visiteur* visiteur = fileAttente.front();
			delete visiteur; // Libérer la mémoire allouée pour chaque visiteur
			fileAttente.pop();
		}
	}
}


// Destructeur
Parc::~Parc() {}