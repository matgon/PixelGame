#pragma once

#include "Common.h"
#include "Tile.h"
#include <vector>

class Grid {
public:
    Grid() = default;
    Grid(int rows, int cols): rows(rows), cols(cols), tiles(rows, std::vector<Tile>(cols)) {
        if (!blocksSpriteSheet.loadFromFile("assets/sprites/Blocks.png")) {
            std::cerr << "Error cargando las texturas de los bloques." << std::endl;
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++) {
                tiles[i][j] = Tile(i, j, blocksSpriteSheet);//emplace_back(i, j, blocksSpriteSheet);
            }
        }
        if (cols == 0) rows = 2;
        
    };
    ~Grid() = default;
    
    void init();
    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                tiles[i][j].draw(window);
            }
        }
    };

    Tile getTile(int gridX, int gridY) {
        return tiles[gridX][gridY];
    }

private:
    int rows, cols;
    std::vector<std::vector<Tile>> tiles;
    sf::Texture blocksSpriteSheet;
};