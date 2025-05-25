#pragma once
#include "Common.h"
#include <random>

class Tileset {
public:

private:

protected:
	sf::Texture texture;
};


class Tile: public Tileset {
public:
	Tile() = default;
	Tile(int gridX, int gridY, const sf::Texture& texture): gridX(gridX), gridY(gridY) {
		topSprite.setTexture(texture);
		topSpriteHover.setTexture(texture);
		bottomSprite.setTexture(texture);
		bottomSpriteHover.setTexture(texture);
		
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<> distrib(0, 3);
		int randomNum = distrib(gen);
		
		topSprite.setTextureRect(sf::IntRect(randomNum * 40, 0, 40, 19));
		topSpriteHover.setTextureRect(sf::IntRect(randomNum * 40, 0, 40, 19));
		bottomSprite.setTextureRect(sf::IntRect(randomNum * 40, 20, 40, 31));
		bottomSpriteHover.setTextureRect(sf::IntRect(randomNum * 40, 20, 40, 31));
				
		topSprite.setPosition(200 + (gridX - gridY) * (tileWidth /2), 
							200 + (gridX + gridY) * (tileHeight / 2));
		topSpriteHover.setPosition(200 + (gridX - gridY) * (tileWidth / 2),
			200 + (gridX + gridY) * (tileHeight / 2)-4);
		bottomSprite.setPosition(200 + (gridX - gridY) * (tileWidth / 2),
			200 + tileHeight / 2 +  (gridX + gridY) * (tileHeight / 2));
		bottomSpriteHover.setPosition(200 + (gridX - gridY) * (tileWidth / 2),
			200 + tileHeight / 2 + (gridX + gridY) * (tileHeight / 2)-4);
	};
	~Tile() = default;

	void draw(sf::RenderWindow& window) {

		isMouseOverSprite(topSprite, window) ? hover = true: hover = false;
		if (hover) {
			window.draw(bottomSpriteHover);
			window.draw(topSpriteHover);
		}
		else {
			window.draw(bottomSprite);
			window.draw(topSprite);
		}
	}
	
	bool getHover() {
		return hover;
	}

	void setHover(const bool& v) {
		hover = v;
	}

	int getGridX() {
		return gridX;
	}

	int getGridY() {
		return gridY;
	}

	sf::FloatRect getWorldPos() {
		return topSprite.getGlobalBounds();
	}

private:

	float tileWidth = 40.0f;
	float tileHeight = 20.0f;
	int gridX;
	int gridY;
	bool hover = false;
	sf::Sprite topSprite;
	sf::Sprite topSpriteHover;
	sf::Sprite bottomSprite;
	sf::Sprite bottomSpriteHover;
};