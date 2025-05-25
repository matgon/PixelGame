#pragma once
#include "Common.h"

class GameEntity {
public:
	GameEntity(float x, float y, const char* path): gridX(x), gridY(y){
		if (!texture.loadFromFile(path)) {
			std::cerr << "Error al cargar la imagen" << std::endl;
		}
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 19, 18));
		sprite.setPosition(x, y);
	};
	virtual ~GameEntity() { std::cout << "Destruyendo instancia de la clase GameEntity..."<<std::endl; };
	float getX() const { return x; };
	float getY() const { return y; };
	sf::Sprite sprite;

protected:
	sf::Texture texture;
	void setX(float n) { x = n; } ;
	void setY(float n) { y = n; };
	int gridX;
	int gridY;
	float x;
	float y;

private:
};