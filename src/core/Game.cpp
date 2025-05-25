#include "Game.h"

Game::Game() {
    window.create(sf::VideoMode(800, 600), "Pixel Art Game");
    window.setFramerateLimit(144);
    currentView = window.getDefaultView();
    currentHUDView = window.getDefaultView();
}

void Game::run() {
    init();
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();
        player->move(deltaTime);
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::init() {
    grid = new Grid(30, 30);
    player = new Player(5.f, 200.f, 5.f, 5.f, 2, 2);
    player->setTile(grid->getTile(2,2));
    mouseHoverTexture.loadFromFile("assets/sprites/mouse.png");
    mouseSprite.setTexture(mouseHoverTexture);
    window.setMouseCursorVisible(false);
    font.loadFromFile("assets/fonts/ka1.ttf");
    
    std::ifstream file("assets/words.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            sf::Text text;
            text.setFont(font);
            text.setString(line);
            text.setCharacterSize(30.f); // Tama�o de la fuente
            text.setFillColor(sf::Color::White); // Color del texto

            words.push_back(text);
        }
        file.close();
    }
    else {
        std::cerr << "No se pudo abrir el archivo" << std::endl;
    }
    currentWord = pullWord();
}

void Game::processEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
        switch (event.type) {
        case sf::Event::Closed:
            // Cerrar la ventana
            window.close();
            break;

        case sf::Event::Resized: {
            // Crear una nueva vista ajustada al tama�o de la ventana
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);

            // Ajustar la vista del juego para que ocupe todo el �rea visible sin distorsi�n
            currentView.setSize(visibleArea.width, visibleArea.height);
            currentView.setCenter(visibleArea.width / 2, visibleArea.height / 2);

            // Mantener la vista de la UI sin zoom ni distorsi�n
            currentHUDView.setSize(visibleArea.width, visibleArea.height);
            currentHUDView.setCenter(visibleArea.width / 2, visibleArea.height / 2);
            break;
        }
        case sf::Event::TextEntered:
            if (event.text.unicode < 128) { // Verifica si el car�cter es ASCII
                bool correct = false;
                if (event.text.unicode == '\b') { // Manejo de la tecla de retroceso
                    if (!inputString.empty())
                        inputString.pop_back();
                }
                
                else if (event.text.unicode == ' ') {
                    correct = (inputString == currentWord.getString().toAnsiString());
                    if (correct) {
                        inputString.clear(); // Limpiar la entrada despu�s de verificar
                        currentWord = pullWord();
                    }
                }
                else if (isCharacterValid(event.text.unicode)) {
                    inputString += std::tolower(static_cast<char>(event.text.unicode));
                }
            }
            break;
        case sf::Event::KeyPressed:
            // Manejo de teclas presionadas
            switch (event.key.code) {
                case sf::Keyboard::Escape:
                    // Cerrar la ventana si se presiona Escape
                    window.close();
                    break;
                default:
                    break;
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) &&
                event.key.code == sf::Keyboard::Backspace) {

                // Buscar la �ltima palabra
                size_t lastSpacePos = inputString.find_last_not_of(" \t\n\r");  // Ignorar los espacios en blanco finales
                if (lastSpacePos != std::string::npos) {
                    size_t secondLastSpacePos = inputString.find_last_of(" \t\n\r", lastSpacePos);

                    // Eliminar desde el �ltimo espacio en blanco encontrado hasta el final
                    if (secondLastSpacePos != std::string::npos) {
                        inputString.erase(secondLastSpacePos + 1);  // Mant�n el espacio despu�s de la palabra borrada
                    }
                    else {
                        inputString.clear();  // Si no hay m�s palabras, borrar todo
                    }
                }
            }
            break;

        case sf::Event::KeyReleased:
            // Manejo de teclas soltadas
            std::cout << "Tecla soltada" << std::endl;
            break;

        case sf::Event::MouseButtonPressed:
            // Manejo de botones del rat�n presionados
            switch (event.mouseButton.button) {
            case sf::Mouse::Left:
                std::cout << "Bot�n izquierdo del rat�n presionado" << std::endl;
                isDragging = true;
                lastMousePosition = currentMousePosition;
                break;
            case sf::Mouse::Right:
                std::cout << "Bot�n derecho del rat�n presionado" << std::endl;
                break;
            default:
                break;
            }
            break;
        case sf::Event::MouseWheelScrolled: {
            sf::Vector2i zoomPixelPos = currentMousePosition;
            sf::Vector2f worldPosBeforeZoom = window.mapPixelToCoords(zoomPixelPos, currentView);

            float zoomFactor = (event.mouseWheelScroll.delta < 0) ? ZOOM_IN_FACTOR : ZOOM_OUT_FACTOR;
            // Aplicar el zoom a la vista
            currentView.zoom(zoomFactor);

            // Obtener la nueva posici�n del rat�n en coordenadas del mundo despu�s de aplicar el zoom
            sf::Vector2f worldPosAfterZoom = window.mapPixelToCoords(zoomPixelPos, currentView);

            // Calcular el desplazamiento en coordenadas del mundo
            sf::Vector2f offset = worldPosBeforeZoom - worldPosAfterZoom;

            // Mover la vista con el desplazamiento calculado
            currentView.move(sf::Vector2f(static_cast<int>(offset.x), static_cast<int>(offset.y)));
            break;
        }
        case sf::Event::MouseButtonReleased:
            // Manejo de botones del rat�n soltados
            std::cout << "Bot�n del rat�n soltado" << std::endl;
            switch (event.mouseButton.button) {
            case sf::Mouse::Left:
                isDragging = false;
                break;
            case sf::Mouse::Right:
                std::cout << "Bot�n derecho del rat�n levantado" << std::endl;
                break;
            default:
                break;
            }
            break;

        case sf::Event::MouseMoved:
            if (isDragging) {
                std::cout << "Se esta moviendo la camara" << std::endl;

                sf::Vector2f worldPosBefore = window.mapPixelToCoords(lastMousePosition, currentView);
                sf::Vector2f worldPosAfter = window.mapPixelToCoords(currentMousePosition, currentView);

                sf::Vector2f dragWorldOffset = worldPosBefore - worldPosAfter;

                currentView.move(dragWorldOffset);
                lastMousePosition = currentMousePosition;
            }
            break;
        default:
            break;
        }
        mouseSprite.setPosition(static_cast<float>(currentMousePosition.x), static_cast<float>(currentMousePosition.y));
    }
}

void::Game::inputControl(const sf::Event& event) {

}

bool Game::isCharacterValid(char c) {
    // Expresi�n regular para los caracteres v�lidos
    std::regex validExpression("[a-zA-Z0-9.,!?\'\"()\\- ]");

    // Comprobar si el car�cter coincide con la expresi�n regular
    std::string charStr(1, c);  // Convertir el car�cter a string
    return std::regex_match(charStr, validExpression);
}

void Game::update(float deltaTime) {
    player->update(deltaTime);
}

sf::Text Game::pullWord() {
    std::random_device rd; // Obtiene un n�mero aleatorio del hardware
    std::mt19937 gen(rd()); // Inicializa el generador de n�meros aleatorios
    std::uniform_int_distribution<> dis(0, words.size() - 1); // Distribuci�n uniforme

    // Seleccionar una palabra aleatoria
    int randomIndex = dis(gen);
    sf::Text randomWord = words[randomIndex];
    //randomWord.setCharacterSize(20);
    randomWord.setPosition(window.getSize().x / 2, 0);

    return randomWord;
}

void renderText(sf::RenderWindow& window, const std::string& targetWord, const std::string& userInput, sf::Font& font) {
    float x = window.getSize().x/2;
    float y = 35.f;

    bool incorrectFound = false; // Marca si se ha encontrado una letra incorrecta

    // Recorre cada letra de la entrada del usuario y compara con la palabra objetivo
    for (size_t i = 0; i < userInput.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(30); // Tama�o de la letra
        text.setPosition(x, y);

        // Comparar las letras si a�n no se ha encontrado un error
        if (!incorrectFound && i < targetWord.size() && userInput[i] == targetWord[i]) {
            text.setFillColor(sf::Color::Green); // Letra correcta en verde
        }
        else {
            text.setFillColor(sf::Color::Red); // Letra incorrecta en rojo
            incorrectFound = true; // Marcar que hubo un error
        }

        // Establecer la letra correspondiente
        text.setString(userInput[i]);

        // Dibujar la letra en la pantalla
        window.draw(text);

        // Actualizar la posici�n x para la siguiente letra
        x += text.getGlobalBounds().width - 3;
    }
}

void Game::render() {
    sf::Text posText;
    
    posText.setFont(font);
    posText.setString("Pos X: " + std::to_string(sf::Mouse::getPosition(window).x) + '\n' + "Pos Y: " + std::to_string(sf::Mouse::getPosition(window).y)
        + '\n' + "World pos X: " + std::to_string(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x) + '\n' + "World pos Y: " + std::to_string(window.mapPixelToCoords(sf::Mouse::getPosition(window)).y));
    posText.setCharacterSize(20);

    window.clear();    // Limpia la pantalla
    window.setView(currentView);
    grid->draw(window);
    player->draw(window);
    window.setView(currentHUDView);
    window.draw(posText);
    window.draw(currentWord);
    renderText(window, currentWord.getString(), inputString, font);
    window.draw(mouseSprite);
    window.setView(window.getDefaultView());
    window.display();  // Muestra la pantalla
}
