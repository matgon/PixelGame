#pragma once
#include "Common.h"
#include "GameEntity.h"

class AliveEntity : public GameEntity {
public:
	AliveEntity(float x, float y, float health, float speed, float acceleration, float strength, const char* spritePath) :
		GameEntity(x, y, spritePath), health(health), speed(speed), acceleration(acceleration), strength(strength) {};
	virtual ~AliveEntity() { std::cout << "Destruyendo instancia de la clase AliveEntity..." << std::endl; };

protected:
	float health;
	float speed;
	float acceleration;
	float strength;

private:
	void update(float deltaTime); // Lógica del jugador
	void draw(sf::RenderWindow& ventana); // Renderizado del jugador
	void inputController(); // Manejar las entradas del teclado
	void receiveDamage(int cantidad);
	void performAttack();
};