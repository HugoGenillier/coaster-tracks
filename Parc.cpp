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
        std::cerr << "Erreur : impossible de charger la police Robot-Regular.ttf." << std::endl;
        return;
    }

    // Espacement vertical initial pour les textes des attractions
    float verticalSpacing = 50.0f;

    // Espacement horizontal initial pour les textes des attractions
    float horizontalSpacing = 10.0f;

    // Taille des cases pour chaque attraction
    const float caseWidth = 450.0f;
    const float caseHeight = 75.0f;

    // Couleur violette foncée (#4b37a4)
    sf::Color purpleColor(75, 55, 164);

    // Utiliser la couleur violette foncée pour toutes les cases d'attraction
    std::vector<sf::Color> colors(Attractions.size(), purpleColor);

    // Indice de couleur pour chaque attraction
    size_t colorIndex = 0;

    // Créer une case pour afficher les actions du premier visiteur avec une couleur orange
    sf::RectangleShape visitorActionsCase(sf::Vector2f(1300.0f, 70.0f)); // Augmenter la largeur et la hauteur de la case
    visitorActionsCase.setFillColor(sf::Color(205, 81, 12)); // Couleur orange
    visitorActionsCase.setOutlineColor(sf::Color::Black);
    visitorActionsCase.setOutlineThickness(2);
    visitorActionsCase.setPosition(10, 700); // Ajuster la position de la case

    // Créer un texte pour afficher les actions du premier visiteur
    sf::Text visitorActionsText("", font, 18);
    visitorActionsText.setPosition(visitorActionsCase.getPosition().x + 5, visitorActionsCase.getPosition().y + 5); // Position du texte dans la case

    // Boucle de rendu SFML pour afficher à chaque étape de la simulation
    while (horloge.estEnCours()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Couleur de fond pour l'affichage total
        window.clear(sf::Color::White);

        // Récupérer l'heure actuelle de l'horloge
        int heure = horloge.getHeure();
        int minute = horloge.getMinute();

        // Créer une case pour afficher l'heure avec une couleur orange
        sf::RectangleShape timeCase(sf::Vector2f(200.0f, 50.0f));
        timeCase.setFillColor(sf::Color(205, 81, 12)); // Couleur orange (#cd510c)
        timeCase.setOutlineColor(sf::Color::Black);
        timeCase.setOutlineThickness(2);
        timeCase.setPosition(10, 10); // Position de la case dans la fenêtre
        window.draw(timeCase);

        // Créer un texte pour afficher l'heure avec une taille de police de 30
        sf::Text timeText("Heure : " + std::to_string(heure) + "h" + std::to_string(minute), font, 30);
        timeText.setPosition(15, 15); // Position du texte dans la case
        window.draw(timeText);

        // Début de la position horizontale pour la première attraction de la ligne
        float startX = 10.0f;

        // Dessiner l'état de chaque attraction
        int attractionsOnRow = 0; // Nombre d'attractions sur la ligne actuelle
        for (auto& attraction : Attractions) {
            attraction.AvancerTour(); // Faire avancer la file d'attente et le temps d'attente estimé de l'attraction

            // Créer un rectangle pour représenter la case de l'attraction
            sf::RectangleShape attractionCase(sf::Vector2f(caseWidth, caseHeight));
            attractionCase.setFillColor(colors[colorIndex % colors.size()]);
            attractionCase.setOutlineColor(sf::Color::Black);
            attractionCase.setOutlineThickness(2);
            attractionCase.setPosition(startX, verticalSpacing); // Position de la case dans la fenêtre
            window.draw(attractionCase);

            // Créer un texte pour afficher le nom de l'attraction et le temps d'attente avec une taille de police de 24
            sf::Text attractionText(attraction.GetNom() + " : " + std::to_string(attraction.TempsAttenteEstime()) + " min", font, 30);

            // Calculer la position horizontale en fonction de la position de la case de l'attraction
            float textPosX = startX + 15; // Position horizontale dans la case
            float textPosY = verticalSpacing + 5; // Position verticale dans la case

            // Définir la position du texte
            attractionText.setPosition(textPosX, textPosY); // Position du texte dans la case

            // Dessiner le texte
            window.draw(attractionText);

            // Augmenter l'espacement horizontal pour la prochaine case
            startX += caseWidth + 10.0f;

            // Incrémenter l'indice de couleur pour passer à la prochaine couleur
            colorIndex++;

            // Incrémenter le nombre d'attractions sur la ligne actuelle
            attractionsOnRow++;

            // Si on a atteint 3 attractions sur la ligne, passer à la ligne suivante
            if (attractionsOnRow == 3) {
                attractionsOnRow = 0; // Réinitialiser le compteur d'attractions sur la ligne
                verticalSpacing += caseHeight + 10.0f; // Passer à la ligne suivante
                startX = 10.0f; // Réinitialiser la position horizontale
            }

        }

        // Afficher les actions du premier visiteur
        window.draw(visitorActionsCase);
        visitorActionsText.setString("Actions du premier visiteur : " + Visiteurs.front().GetActions());
        visitorActionsText.setCharacterSize(30); // Augmenter la taille du texte
        visitorActionsText.setPosition(visitorActionsCase.getPosition().x + 10, visitorActionsCase.getPosition().y + 10); // Ajuster la position du texte dans la case
        window.draw(visitorActionsText);

        // Charger l'image du logo avec SFML
        sf::Texture logoTexture;
        if (!logoTexture.loadFromFile("Logo.png")) {
            // Gérer l'erreur si le chargement de l'image a échoué
            std::cerr << "Erreur : impossible de charger l'image du logo." << std::endl;
            return;
        }

        // Créer un sprite pour afficher l'image du logo
        sf::Sprite logoSprite(logoTexture);

        // Redimensionner le logo à 80% de sa taille d'origine
        float scaleFactor = 0.8f;
        logoSprite.setScale(scaleFactor, scaleFactor);
        // Calculer la position X pour placer le logo à droite des cases d'attraction
        float logoPosX = 10 + 3 * (caseWidth + 10) + 50;

        // Centrer le logo verticalement
        float logoPosY = (window.getSize().y - logoTexture.getSize().y * scaleFactor) / 2.0f;

        // Positionner le logo
        logoSprite.setPosition(logoPosX, logoPosY);
        window.draw(logoSprite);

        // Réinitialiser l'espacement vertical pour la prochaine itération
        verticalSpacing = 50.0f;

        // Mettre à jour l'affichage
        window.display();

        // Activer les visiteurs
        for (auto& visiteur : Visiteurs) {
            visiteur.ActiverVisiteur(); // Activer le visiteur
        }

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