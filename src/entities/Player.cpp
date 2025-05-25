#include "Common.h"
#include "Player.h"

void Player::move(float deltaTime) {
    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite.move(-speed * deltaTime, 0.f);
        setX(x + (-speed * deltaTime));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        sprite.move(speed * deltaTime, 0.f);
        setX(x - (-speed * deltaTime));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        sprite.move(0.f, -speed * deltaTime);
        setY(y + (-speed * deltaTime));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        sprite.move(0.f, speed * deltaTime);
        setY(y - (-speed * deltaTime));
    }*/
}

void Player::update(float deltaTime) {
    elapsedTime += deltaTime;
    if (elapsedTime >= 1.f) {
        elapsedTime = 0.f;
        currentFrame++;
        if (currentFrame >= 2) // Suponiendo que tienes 4 frames en la animación
            currentFrame = 0;

        sprite.setTextureRect(sf::IntRect(0, currentFrame*19, 19, 18)); // Cambiar de sprite
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    playerLight->setPosition(x + 10, y + 10);
    playerLight->draw(window);
}

void Player::setTile(Tile tile) {
    sf::FloatRect tileSprite = tile.getWorldPos();
    gridX = tile.getGridX();
    gridY = tile.getGridY();
    setX(tileSprite.getPosition().x);
    setY(tileSprite.getPosition().y);
    sprite.move(sf::Vector2f(x, y));
}
