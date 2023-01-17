//
// Created by Abby on 12/5/2022.
//

#include "Tile.h"

Tile::Tile()
{
    flagHere = 0;
    mineHere = 0;
    isRevealedTile = 0;
}

void Tile::setFlag(bool value)
{
    flagHere = value;
}
void Tile::setRevealed(bool value)
{
    isRevealedTile = value;
}

void Tile::setMine(bool value)
{
    mineHere = value;
}

bool Tile::isRevealed()
{
    return isRevealedTile;
}

bool Tile::getFlag()
{
    return flagHere;
}

bool Tile::isMine()
{
    return mineHere;
}

void Tile::removeFlag() {
    flagHere = false;
}

