#pragma once
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Tile
{
public:
    Tile();
    void setFlag(bool value);
    bool getFlag();
    void removeFlag();
    void setRevealed(bool value);
    bool isRevealed();
    void setMine(bool value);
    bool isMine();
    int getNearbyMines()
    {
        return nearbyMines;
    }
    void setNearbyMines(int numMines)
    {
        nearbyMines = numMines;
    }

private:
    int nearbyMines;
    bool flagHere;
    bool mineHere;
    bool isRevealedTile = false;
};