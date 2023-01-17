#include <SFML/Graphics.hpp>
#include <fstream>
#include "Extras.h"
#include "Board.h"

int main()
{
    Board board;

    sf::Event event;
    int width, height;
    int boardHeight = board.getRows() * 32;
    // Correcting the sizes to how they should be
    width = board.getColumns() * 32;
    height = (board.getRows() * 32) + 100;

    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper 2022");

    /* ========== Below is the actual loop that runs the game: ========== */

    // First reset board display/random generate
    board.generateBoard();

    while (window.isOpen())
    {
        Tile tile;
        window.clear(sf::Color(255, 255, 255));

        //Setting the basic bg color

        // The targeted state is window. This is where the board is going.
        while (window.pollEvent(event))
        {
            switch(event.type)
            {

                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }
                case sf::Event::MouseButtonPressed:
                {

                    // Check for flag texture on tile position
                    int x,y;
                    x = sf::Mouse::getPosition(window).x;
                    int tileX = x/32;
                    y = sf::Mouse::getPosition(window).y;
                    int tileY = y/32;

                    if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    {
                        if(!board.isLoss() && !board.isWin()) {
                            // Flag the tile
                            if (y < height) {
                                board.placeFlag(tileX, tileY);
                            }
                            // Now subtract from flag/mine count in bottom left:
                        }
                    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        int smileX = (width/2) - 32;
                        int map[25][16];

                        if(!board.isLoss() && !board.isWin())
                        {
                            board.checkWin();

                            // Check based on the tile position if it's value correlated to a bomb, if not:
                            if(y < boardHeight) {
                                board.revealTile(tileX, tileY);
                            } else
                            {
                                //Smile First: RESET
                                if(y < boardHeight + 64 && x > smileX && x < smileX + 64)
                                {
                                    board.reset();
                                    board.generateBoard();
                                }
                                // Debug
                                if(y < boardHeight + 64 && x > smileX + 64 * 2 && x < smileX + 64 * 3)
                                {
                                    board.toggleDebug();
                                }
                                // Boards:
                                if(y < boardHeight + 64 && x > smileX + 64 * 3 && x < smileX + 64 * 4)
                                {
                                    board.reset();
                                    board.readTestBoard(map,"testboard1.brd");

                                }
                                if(y < boardHeight + 64 && x > smileX + 64 * 4 && x < smileX + 64 * 5)
                                {
                                    board.reset();
                                    board.readTestBoard(map,"testboard2.brd");

                                }
                                if(y < boardHeight + 64 && x > smileX + 64 * 5 && x < smileX + 64 * 6)
                                {
                                    board.reset();
                                    board.readTestBoard(map,"testboard3.brd");
                                }
                            }
                        } else {
                            if (y < boardHeight + 64 && x > smileX && x < smileX + 64 && y > boardHeight) {
                                board.reset();
                                board.generateBoard();
                            }
                            if(y < boardHeight + 64 && x > smileX + 64 * 3 && x < smileX + 64 * 4 && y > boardHeight)
                            {
                                board.reset();
                                board.readTestBoard(map,"testboard1.brd");
                            }
                            if(y < boardHeight + 64 && x > smileX + 64 * 4 && x < smileX + 64 * 5 && y > boardHeight)
                            {
                                board.reset();
                                board.readTestBoard(map,"testboard2.brd");
                            }
                            if(y < boardHeight + 64 && x > smileX + 64 * 5 && x < smileX + 64 * 6 && y > boardHeight)
                            {
                                board.reset();
                                board.readTestBoard(map,"testboard3.brd");
                            }
                        }
                    }
                    break;
                }
            }
        }
        board.displayBoard(window);
        window.display();
    }
    return 0;
}