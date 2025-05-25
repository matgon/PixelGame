#include "Common.h"

bool isMouseOverSprite(const sf::Sprite& sprite, const sf::RenderWindow& window) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePos);

	sf::FloatRect spriteBounds = sprite.getGlobalBounds();

	if (!spriteBounds.contains(static_cast<float>(mouseWorldPos.x), static_cast<float>(mouseWorldPos.y))) {
		return false;
	}

	sf::Vector2f localMousePos = sprite.getInverseTransform().transformPoint(static_cast<float>(mouseWorldPos.x), static_cast<float>(mouseWorldPos.y));

	const sf::Texture* texture = sprite.getTexture();
	if (texture == nullptr) {
		return false;
	}

	sf::IntRect textureRect = sprite.getTextureRect();

	if (localMousePos.x < 0 || localMousePos.x >= textureRect.width ||
		localMousePos.y < 0 || localMousePos.y >= textureRect.height) {
		return false;
	}

	sf::Color pixelColor = texture->copyToImage().getPixel(static_cast<unsigned int>(textureRect.left + static_cast<int>(localMousePos.x)),
		static_cast<unsigned int>(textureRect.top + static_cast<int>(localMousePos.y)));

	return pixelColor.a != 0;
}