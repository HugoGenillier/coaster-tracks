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

    // Couleur violette fonc�e (#4b37a4)
    sf::Color purpleColor(75, 55, 164);

    // Utiliser la couleur violette fonc�e pour toutes les cases d'attraction
    std::vector<sf::Color> colors(Attractions.size(), purpleColor);

    // Indice de couleur pour chaque attraction
    size_t colorIndex = 0;

    // Cr�er une case pour afficher les actions du premier visiteur avec une couleur orange
    sf::RectangleShape visitorActionsCase(sf::Vector2f(1300.0f, 70.0f)); // Augmenter la largeur et la hauteur de la case
    visitorActionsCase.setFillColor(sf::Color(205, 81, 12)); // Couleur orange
    visitorActionsCase.setOutlineColor(sf::Color::Black);
    visitorActionsCase.setOutlineThickness(2);
    visitorActionsCase.setPosition(10, 700); // Ajuster la position de la case

    // Cr�er un texte pour afficher les actions du premier visiteur
    sf::Text visitorActionsText("", font, 18);
    visitorActionsText.setPosition(visitorActionsCase.getPosition().x + 5, visitorActionsCase.getPosition().y + 5); // Position du texte dans la case

    // Boucle de rendu SFML pour afficher � chaque �tape de la simulation
    while (horloge.estEnCours()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Couleur de fond pour l'affichage total
        window.clear(sf::Color::White);

        // R�cup�rer l'heure actuelle de l'horloge
        int heure = horloge.getHeure();
        int minute = horloge.getMinute();

        // Cr�er une case pour afficher l'heure avec une couleur orange
        sf::RectangleShape timeCase(sf::Vector2f(200.0f, 50.0f));
        timeCase.setFillColor(sf::Color(205, 81, 12)); // Couleur orange (#cd510c)
        timeCase.setOutlineColor(sf::Color::Black);
        timeCase.setOutlineThickness(2);
        timeCase.setPosition(10, 10); // Position de la case dans la fen�tre
        window.draw(timeCase);

        // Cr�er un texte pour afficher l'heure avec une taille de police de 30
        sf::Text timeText("Heure : " + std::to_string(heure) + "h" + std::to_string(minute), font, 30);
        timeText.setPosition(15, 15); // Position du texte dans la case
        window.draw(timeText);

        // D�but de la position horizontale pour la premi�re attraction de la ligne
        float startX = 10.0f;

        // Dessiner l'�tat de chaque attraction
        int attractionsOnRow = 0; // Nombre d'attractions sur la ligne actuelle
        for (auto& attraction : Attractions) {
            attraction.AvancerTour(); // Faire avancer la file d'attente et le temps d'attente estim� de l'attraction

            // Cr�er un rectangle pour repr�senter la case de l'attraction
            sf::RectangleShape attractionCase(sf::Vector2f(caseWidth, caseHeight));
            attractionCase.setFillColor(colors[colorIndex % colors.size()]);
            attractionCase.setOutlineColor(sf::Color::Black);
            attractionCase.setOutlineThickness(2);
            attractionCase.setPosition(startX, verticalSpacing); // Position de la case dans la fen�tre
            window.draw(attractionCase);

            // Cr�er un texte pour afficher le nom de l'attraction et le temps d'attente avec une taille de police de 24
            sf::Text attractionText(attraction.GetNom() + " : " + std::to_string(attraction.TempsAttenteEstime()) + " min", font, 30);

            // Calculer la position horizontale en fonction de la position de la case de l'attraction
            float textPosX = startX + 15; // Position horizontale dans la case
            float textPosY = verticalSpacing + 5; // Position verticale dans la case

            // D�finir la position du texte
            attractionText.setPosition(textPosX, textPosY); // Position du texte dans la case

            // Dessiner le texte
            window.draw(attractionText);

            // Augmenter l'espacement horizontal pour la prochaine case
            startX += caseWidth + 10.0f;

            // Incr�menter l'indice de couleur pour passer � la prochaine couleur
            colorIndex++;

            // Incr�menter le nombre d'attractions sur la ligne actuelle
            attractionsOnRow++;

            // Si on a atteint 3 attractions sur la ligne, passer � la ligne suivante
            if (attractionsOnRow == 3) {
                attractionsOnRow = 0; // R�initialiser le compteur d'attractions sur la ligne
                verticalSpacing += caseHeight + 10.0f; // Passer � la ligne suivante
                startX = 10.0f; // R�initialiser la position horizontale
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
            // G�rer l'erreur si le chargement de l'image a �chou�
            std::cerr << "Erreur : impossible de charger l'image du logo." << std::endl;
            return;
        }

        // Cr�er un sprite pour afficher l'image du logo
        sf::Sprite logoSprite(logoTexture);

        // Redimensionner le logo � 80% de sa taille d'origine
        float scaleFactor = 0.8f;
        logoSprite.setScale(scaleFactor, scaleFactor);
        // Calculer la position X pour placer le logo � droite des cases d'attraction
        float logoPosX = 10 + 3 * (caseWidth + 10) + 50;

        // Centrer le logo verticalement
        float logoPosY = (window.getSize().y - logoTexture.getSize().y * scaleFactor) / 2.0f;

        // Positionner le logo
        logoSprite.setPosition(logoPosX, logoPosY);
        window.draw(logoSprite);

        // R�initialiser l'espacement vertical pour la prochaine it�ration
        verticalSpacing = 50.0f;

        // Mettre � jour l'affichage
        window.display();

        // Activer les visiteurs
        for (auto& visiteur : Visiteurs) {
            visiteur.ActiverVisiteur(); // Activer le visiteur
        }

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