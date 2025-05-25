#pragma once  // Previene inclusiones múltiples

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <regex>

bool isMouseOverSprite(const sf::Sprite& sprite, const sf::RenderWindow& window);