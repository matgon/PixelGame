#pragma once
#include "Common.h"
#include "Player.h"
#include "Grid.h"

class Game {
public:
    Game();
    ~Game() {
        if (player != nullptr) delete player;
        if (grid != nullptr) delete grid; 
        std::cout << "Destruyendo la clase Game" << std::endl;
    };

    void run();

private:
    void init();
    void processEvents();
    void update(float deltaTime);
    sf::Text pullWord();
    void render();
    void inputControl(const sf::Event& event);
    bool isCharacterValid(char c);

    sf::Clock clock;
    Player* player = nullptr;
    Grid* grid = nullptr;

    std::vector<sf::Text> words;
    sf::Font font;
    sf::Text currentWord;
    std::string inputString;
    sf::Text inputWord;

    const float ZOOM_OUT_FACTOR = 0.5f;
    const float ZOOM_IN_FACTOR = 2.0f;
    float scaleFactorX = 1.f;
    float scaleFactorY = 1.f;
    bool isDragging = false;

    sf::Texture mouseHoverTexture;
    sf::Sprite mouseSprite;

    sf::Vector2i lastMousePosition;
    sf::View currentView;
    sf::View currentHUDView;
    sf::RenderWindow window;
};
