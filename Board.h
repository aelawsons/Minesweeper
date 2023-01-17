#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <sstream>
#include "Extras.h"
#include "Tile.h"

using namespace std;

class Board {
public:
    Board();
    void displayBoard(sf::RenderTarget &board);

    int getColumns() const { return columns; }
    int getRows() const { return rows; }

    void revealTile(int x, int y);
    void placeFlag(int x, int y);

    void generateBoard();
    void readTestBoard(int map[25][16], string filename);

    void setTileNumbers();
    void clearZeros(int x, int y);
    void toggleDebug();

    void reset();

    bool isLoss()
    {
        return loser;
    }
    void setLoss(bool value)
    {
        loser = value;
    }
    bool isWin()
    {
        return winner;
    }
    void setWin(bool value)
    {
        winner = value;
    }
    void checkWin();

    void getMineImg(int position, int value, sf::RenderTarget &board);

private:
    vector<vector<Tile>> tileVector;

    sf::Sprite oneSpot;
    sf::Sprite tenSpot;
    sf::Sprite hundredSpot;
    sf::Sprite negatives;

    int columns,rows,mineCount;
    int fileMineCount;
    int realMineCount;
    bool debugMode = false;
    bool winner = false;
    bool loser = false;
    void readConfigFile();
    int cornerCount = 0;
    map<string, sf::Texture> textureMap = loadTextureFiles();

};