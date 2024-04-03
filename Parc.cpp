#include "Parc.h"
#include <iomanip>

Parc::Parc(std::string nom) : Nom(nom), Attractions(), Visiteurs() {}

void Parc::AfficherDetails() const {
	cout << "Nom : " << Nom << endl;
}

// Ajoute l'attraction � la liste des attractions du parc
void Parc::AjouterAttraction(const Attraction& attraction) {
	Attractions.push_back(attraction);
}

//M�thode de simulation, elle g�re l'affichage et met � jour les objets selon une boucle it�rative
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

    // Espacement vertical et horizontal initial pour les textes des attractions
    float verticalSpacing = 50.0f;
    float horizontalSpacing = 10.0f;

    // D�finition de la taille des cases pour chaque attraction
    const float caseWidth = 450.0f;
    const float caseHeight = 75.0f;

    // Utiliser la couleur violette fonc�e pour toutes les cases d'attraction
    sf::Color purpleColor(75, 55, 164);
    std::vector<sf::Color> colors(Attractions.size(), purpleColor);

    // Indice de couleur pour chaque attraction
    size_t colorIndex = 0;

    // Cr�er une case pour afficher les actions du premier visiteur avec une couleur orange
    sf::RectangleShape visitorActionsCase(sf::Vector2f(1300.0f, 70.0f));
    visitorActionsCase.setFillColor(sf::Color(205, 81, 12));
    visitorActionsCase.setOutlineColor(sf::Color::Black);
    visitorActionsCase.setOutlineThickness(2);
    visitorActionsCase.setPosition(10, 700);

    // Cr�er un texte pour afficher les actions du premier visiteur
    sf::Text visitorActionsText("", font, 18);
    visitorActionsText.setPosition(visitorActionsCase.getPosition().x + 5, visitorActionsCase.getPosition().y + 5);

    // Boucle pour afficher � chaque �tape de la simulation avec SFML
    while (horloge.estEnCours()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // D�finition de la couleur de fond pour l'affichage total
        window.clear(sf::Color::White);

        // R�cup�rer et afficher l'heure actuelle de l'horloge de simulation
        int heure = horloge.getHeure();
        int minute = horloge.getMinute();
        //Cr�ation de la case
        sf::RectangleShape timeCase(sf::Vector2f(200.0f, 50.0f));
        timeCase.setFillColor(sf::Color(205, 81, 12));
        timeCase.setOutlineColor(sf::Color::Black);
        timeCase.setOutlineThickness(2);
        timeCase.setPosition(10, 10);
        window.draw(timeCase);
        // Cr�ation du texte pour afficher l'heure
        sf::Text timeText("Heure : " + std::to_string(heure) + "h" + std::to_string(minute), font, 30);
        timeText.setPosition(15, 15);
        window.draw(timeText);


        // D�finition de la position horizontale pour la premi�re attraction de la liste
        float startX = 10.0f;
        // Afficher l'�tat de chaque attraction
        int attractionsOnRow = 0;
        for (auto& attraction : Attractions) {
            attraction.AvancerTour(); // Faire avancer la files d'attente et estimer le nouveau temps d'attente
            // Cr�er une case pour repr�senter la case de l'attraction
            sf::RectangleShape attractionCase(sf::Vector2f(caseWidth, caseHeight));
            attractionCase.setFillColor(colors[colorIndex % colors.size()]);
            attractionCase.setOutlineColor(sf::Color::Black);
            attractionCase.setOutlineThickness(2);
            attractionCase.setPosition(startX, verticalSpacing);
            window.draw(attractionCase);
            // Cr�er un texte pour afficher le nom de l'attraction et le temps d'attente
            sf::Text attractionText(attraction.GetNom() + " : " + std::to_string(attraction.TempsAttenteEstime()) + " min", font, 30);
            // Calculer la position horizontale et verticale
            float textPosX = startX + 15;
            float textPosY = verticalSpacing + 5;
            // D�finir la position du texte
            attractionText.setPosition(textPosX, textPosY);
            // Ecrire le texte
            window.draw(attractionText);

            // Augmenter l'espacement horizontal pour la prochaine case
            startX += caseWidth + 10.0f;
            colorIndex++;
            // Incr�menter le nombre d'attractions sur la ligne actuelle
            attractionsOnRow++;

            // Si on a atteint 3 attractions sur la ligne, passer � la ligne suivante
            if (attractionsOnRow == 3) {
                attractionsOnRow = 0;
                verticalSpacing += caseHeight + 10.0f;
                startX = 10.0f;
            }

        }

        // Afficher les actions du premier visiteur pour montrer un exemple
        window.draw(visitorActionsCase);
        visitorActionsText.setString("Actions du premier visiteur : " + Visiteurs.front().GetActions());
        visitorActionsText.setCharacterSize(30); // Augmenter la taille du texte
        visitorActionsText.setPosition(visitorActionsCase.getPosition().x + 10, visitorActionsCase.getPosition().y + 10); // Ajuster la position du texte dans la case
        window.draw(visitorActionsText);

        // Mettre le logo
        sf::Texture logoTexture;
        if (!logoTexture.loadFromFile("Logo.png")) {
            // G�rer l'erreur si le chargement de l'image a �chou�
            std::cerr << "Erreur : impossible de charger l'image du logo." << std::endl;
            return;
        }
        sf::Sprite logoSprite(logoTexture);
        float scaleFactor = 0.8f;
        logoSprite.setScale(scaleFactor, scaleFactor);
        float logoPosX = 10 + 3 * (caseWidth + 10) + 50;
        float logoPosY = (window.getSize().y - logoTexture.getSize().y * scaleFactor) / 2.0f;
        logoSprite.setPosition(logoPosX, logoPosY);
        window.draw(logoSprite);

        verticalSpacing = 50.0f;

        // Mettre � jour l'affichage
        window.display();

        // Activer les visiteurs dans la simulation
        for (auto& visiteur : Visiteurs) {
            visiteur.ActiverVisiteur();
        }

        // Attendre une seconde pour l'affichage
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Fin de la journ�e dans le parc\n";
}

//M�thode pour lib�rer la m�moire allou�e pour chaque visiteur
void Parc::Lib�rerVisiteurs() {
	for (Attraction& attraction : Attractions) {
		std::queue<Visiteur*>& fileAttente = attraction.GetFileAttente();
		while (!fileAttente.empty()) {
			Visiteur* visiteur = fileAttente.front();
			delete visiteur;
			fileAttente.pop();
		}
	}
}

Parc::~Parc() {}