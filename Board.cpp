
#include "Board.h"
#include <random>

Board::Board()
{
    readConfigFile();
    for (int i = 0; i < rows; ++i)
    {
        vector<Tile> rowTiles;
        for (int j = 0; j < columns; ++j)
        {
            Tile tile;
            rowTiles.push_back(tile);
        }
        tileVector.push_back(rowTiles);
    }
}

/* === DISPLAY THE BOARD === */
void Board::displayBoard(sf::RenderTarget &board)
{
    sf::Sprite tileSprite;
    sf::Sprite smileSprite;

    smileSprite.setTexture(textureMap["face_happy"]);
    int smileWidth = (columns/2) *  32 - 64;
    int smileHeight = (rows * 32) ;
    smileSprite.setPosition(smileWidth + 48,smileHeight);
    board.draw(smileSprite);

    sf::Sprite debugButton;
    debugButton.setTexture(textureMap["debug"]);
    debugButton.setPosition(smileWidth + 48 + 64 *2, smileHeight);
    board.draw(debugButton);

    sf::Sprite buttonOne;
    buttonOne.setTexture(textureMap["test_1"]);
    buttonOne.setPosition(smileWidth  + 48 + 64*3,smileHeight);
    board.draw(buttonOne);

    sf::Sprite buttonTwo;
    buttonTwo.setTexture(textureMap["test_2"]);
    buttonTwo.setPosition(smileWidth + 48 + 64 *4,smileHeight);
    board.draw(buttonTwo);

    sf::Sprite buttonThree;
    buttonThree.setTexture(textureMap["test_3"]);
    buttonThree.setPosition(smileWidth + 48 +  64 * 5,smileHeight);
    board.draw(buttonThree);



    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            board.draw(negatives);
            board.draw(hundredSpot);
            board.draw(tenSpot);
            board.draw(oneSpot);
            tileSprite.setPosition(j * 32, i *32 );
            Tile tile = tileVector[i][j];
            if(tile.isRevealed())
            {
                tileSprite.setTexture(textureMap["tile_revealed"]);
                board.draw(tileSprite);

                switch(tile.getNearbyMines()) {
                    case 1:
                        tileSprite.setTexture(textureMap["number_1"]);
                        break;
                    case 2:
                        tileSprite.setTexture(textureMap["number_2"]);
                        break;
                    case 3:
                        tileSprite.setTexture(textureMap["number_3"]);
                        break;

                    case 4:
                        tileSprite.setTexture(textureMap["number_4"]);
                        break;

                    case 5:
                        tileSprite.setTexture(textureMap["number_5"]);
                        break;

                    case 6:
                        tileSprite.setTexture(textureMap["number_6"]);
                        break;

                    case 7:
                        tileSprite.setTexture(textureMap["number_7"]);
                        break;

                    case 8:
                        tileSprite.setTexture(textureMap["number_8"]);
                        break;
                }
            } if(!tile.isRevealed())
            {
                tileSprite.setTexture(textureMap["tile_hidden"]);
            } if(tile.getFlag())
            {
                tileSprite.setTexture(textureMap["tile_hidden"]);
                board.draw(tileSprite);
                tileSprite.setTexture(textureMap["flag"]);
            } if(tile.isMine() && tile.isRevealed())
            {
                tileSprite.setTexture(textureMap["mine"]);
                smileSprite.setTexture(textureMap["face_lose"]);
                board.draw(smileSprite);
                setLoss(true);

            } if(debugMode && tile.isMine())
            {
                tileSprite.setTexture(textureMap["tile_hidden"]);
                board.draw(tileSprite);
                tileSprite.setTexture(textureMap["mine"]);
            }
            if(debugMode && tile.getFlag() && tile.isMine())
            {
                tileSprite.setTexture(textureMap["tile_hidden"]);
                board.draw(tileSprite);
                tileSprite.setTexture(textureMap["flag"]);
                board.draw(tileSprite);
                tileSprite.setTexture(textureMap["mine"]);
            }
            if(isWin())
            {
                if(tile.isMine()) {
                    tileSprite.setTexture(textureMap["tile_hidden"]);
                    board.draw(tileSprite);
                    tileSprite.setTexture(textureMap["flag"]);
                }
                smileSprite.setTexture(textureMap["face_win"]);
                board.draw(smileSprite);
            }
            //Set the height of the num counter and then call the function:
            getMineImg(rows * 32, cornerCount, board);
            board.draw(tileSprite);
        }
    }

}

void Board::readConfigFile()
{
    string line;
    fstream config("boards/config.cfg");

    // Getting the info according to the project sheet:
    getline(config, line);
    this->columns = stoi(line);
    getline(config, line);
    this->rows = stoi(line);
    // Mine/Bomb Count:
    getline(config, line);
    this->mineCount = stoi(line);

    cornerCount = mineCount;
    realMineCount = mineCount;
}

void Board::revealTile(int x, int y)
{
    if(!tileVector[y][x].getFlag()) {
        if (tileVector[y][x].isMine()) {
            for (int i = 0; i < tileVector.size(); i++) {
                for (int j = 0; j < tileVector[0].size(); j++) {
                    if (tileVector[i][j].isMine()) {
                        tileVector[i][j].setRevealed(true);
                    }
                }
            }
        } else if (tileVector[y][x].getNearbyMines() == 0) {
            clearZeros(x, y);
        }
        tileVector[y][x].setRevealed(true);
    }
    checkWin();

}

void Board::placeFlag(int x, int y)
{
    //If a flag isn't on the tile, place it. If it is, remove it.
    if(!tileVector[y][x].getFlag() && !tileVector[y][x].isRevealed())
    {
        tileVector[y][x].setFlag(true);
        cornerCount --;

    } else if(tileVector[y][x].getFlag() && !tileVector[y][x].isRevealed())
    {
        tileVector[y][x].removeFlag();
        cornerCount ++;
    }
}

// All test boards are 25 x 16
void Board::readTestBoard(int map[25][16], string fileName) {
    ifstream readFile("boards/" + fileName);
    fileMineCount = 0;
    if(readFile.good())
    {
        string iter;
        int i = 0;
        while(getline(readFile, iter))
        {
            for(int j = 0; j < iter.size(); j++)
            {
                map[j][i] = iter[j] - '0';
            }
            i++;
        }
    }
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            if (map[j][i] == 1)
            {
                tileVector[i][j].setMine(true);
                fileMineCount ++;
            }
        }
    }
    columns = 25;
    rows = 16;
    mineCount = fileMineCount;
    cornerCount = fileMineCount;
    //Had to set this value to use a counter in checkWin
    setTileNumbers();
    readFile.close();
}

void Board::generateBoard() {
    //Going to randomly find an x and y, check if it's a bomb, and if not add a bomb
    //then increment.
    for(int i = 0; i < realMineCount; i++)
    {
        int generatedX = rand() % columns;
        int generatedY = rand() % rows;
        while(tileVector[generatedY][generatedX].isMine())
        {
            generatedX = rand() % columns;
            generatedY = rand() % rows;
        }
        tileVector[generatedY][generatedX].setMine(true);
        mineCount++;
    }
    setTileNumbers();
}

void Board::reset() {
    //clear the board then regenerate
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++) {
            tileVector[i][j].setRevealed(false);
            tileVector[i][j].setFlag(false);
            tileVector[i][j].setMine(false);
        }
    }
    cornerCount = realMineCount;
    mineCount = 0;
    setLoss(false);
    setWin(false);
}

void Board::setTileNumbers() {
    for(int i = 0; i < rows; i ++)
    {
        for(int j = 0; j < columns; j++)
        {
            int counter = 0;
            if(i < rows - 1 && tileVector[i+1][j].isMine())
            {
                counter++;
            }
            if(i > 0 && tileVector[i -1][j].isMine())
            {
                counter++;
            }
            if(j < columns - 1 && tileVector[i][j+1].isMine())
            {
                counter++;
            }
            if(j > 0 && tileVector[i][j-1].isMine())
            {
                counter++;
            }
            if(i < rows - 1 && j < columns - 1 && tileVector[i+1][j+1].isMine())
            {
                counter++;
            }
            if(i > 0 && j > 0 && tileVector[i-1][j-1].isMine())
            {
                counter++;
            }
            if(i < rows - 1 && j > 0 && tileVector[i+1][j-1].isMine())
            {
                counter++;
            }
            if(i > 0 && j < columns - 1 && tileVector[i-1][j+1].isMine())
            {
                counter++;
            }
            tileVector[i][j].setNearbyMines(counter);
        }
    }
}

void Board::toggleDebug() {
    debugMode = !debugMode;
}

void Board::clearZeros(int x, int y) {
    if(tileVector[y][x].getNearbyMines() == 0 && !tileVector[y][x].getFlag() && !tileVector[y][x].isRevealed())
    {
        tileVector[y][x].setRevealed(true);
        if(x > 0 && y > 0)
            clearZeros(x - 1, y - 1);
        if(y > 0)
            clearZeros(x, y - 1);
        if(x < columns - 1 && y > 0)
            clearZeros(x + 1, y - 1);
        if(x < columns -1)
            clearZeros(x + 1, y);
        if(x < columns - 1 && y < rows - 1 )
            clearZeros(x + 1, y + 1);
        if(y < rows - 1)
            clearZeros(x, y + 1);
        if(x > 0 && y < rows -1)
            clearZeros(x - 1, y + 1);
        if(x > 0)
            clearZeros(x - 1, y);

    } else if(!tileVector[y][x].getFlag() && !tileVector[y][x].isRevealed())
    {
        tileVector[y][x].setRevealed(true);
    }
    checkWin();
}

void Board::checkWin() {
    // To check win, count number of reveals that arent mines. If this
    // == to total Mine count, then you won!
    int counterMines = 0;
    int notMines = (rows * columns) - mineCount;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++) {
            if(tileVector[i][j].isRevealed() && !tileVector[i][j].isMine())
            {
               counterMines++;
            }
        }
    }
    if(counterMines == notMines) {
        setWin(true);
        cornerCount = 0;
    }
}

void Board::getMineImg(int position, int value, sf::RenderTarget &board) {
    // read in the number of minesRemaining/changing and update the bottom left image accordingly.
    value = cornerCount;
    int temp = cornerCount;

    sf::Sprite digitsPlace;
    digitsPlace.setTexture(textureMap["digits"]);

    sf::Sprite negativePlace;
    negativePlace.setTexture(textureMap["digits"]);
    negativePlace.setTextureRect(sf::IntRect(210, 0 , 21, 32));
    negativePlace.setPosition(0, position);

    if(value < 0)
    {
        board.draw(negativePlace);
        //Once you've used value, absolute value it, so you can carry on to the
        // Next part
        value = abs(value);
    }
    // Getting the ones values for the 3-digit number
    int ones,tens,hundreds;
    temp = value;
    //using division and remainder, we can find each digit.
    ones = temp%10;
    //63 comes from 21 * 3, and so on for the other x's
    digitsPlace.setPosition(63, position);
    digitsPlace.setTextureRect(sf::IntRect(21 * ones, 0, 21, 32));
    board.draw(digitsPlace);

    tens = (temp/10)%10;
    digitsPlace.setPosition(42, position);
    digitsPlace.setTextureRect(sf::IntRect(21 * tens, 0, 21, 32));
    board.draw(digitsPlace);

    hundreds = (temp/100)%10;
    digitsPlace.setPosition(21, position);
    digitsPlace.setTextureRect(sf::IntRect(21 * hundreds, 0 , 21, 32));
    board.draw(digitsPlace);

}


