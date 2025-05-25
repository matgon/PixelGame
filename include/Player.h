#pragma once
#include "Common.h"
#include "AliveEntity.h"
#include "Light.h"
#include "Tile.h"

class Player : public AliveEntity {
public:
	Player() = default;
	Player(float health, float speed, float acceleration, float strength, float x, float y) :
		AliveEntity(x, y, health, speed, acceleration, strength, "assets/sprites/Player.png") {
		playerLight = new Light(50.f, 50.f); playerLight->setPosition(x + 10, y + 10);
	};
	~Player() { std::cout << "Destruyendo instancia de la clase Player..." << std::endl; playerLight->~Light(); };

	void move(float deltaTime);
	void update(float elapsedTime);
	void draw(sf::RenderWindow& window);
	void setTile(Tile tile);
private:

	Light* playerLight = nullptr;
	float elapsedTime = 0.f;
	int currentFrame = 0;
};