#pragma once
#include "Common.h"
#include "AliveEntity.h"
#include "Tile.h"
#include "Light.h"

class Enemy : public AliveEntity {
public:
	Enemy() = default;
	Enemy(float health, float speed, float acceleration, float strength, float x, float y) :
		AliveEntity(x, y, health, speed, acceleration, strength, "assets/sprites/Player.png") {
		playerLight = new Light(50.f, 50.f); playerLight->setPosition(x + 10, y + 10);
	};
	~Enemy() { std::cout << "Destruyendo instancia de la clase Player..." << std::endl; playerLight->~Light(); };

	void move(float deltaTime);
	void update(float elapsedTime);
	void draw(sf::RenderWindow& window);
	void setTile(Tile tile);
	
private:

	Light* playerLight = nullptr;
	float elapsedTime = 0.f;
	int currentFrame = 0;
};