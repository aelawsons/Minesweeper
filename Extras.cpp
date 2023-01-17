#include "Extras.h"

map<string, sf::Texture> loadTextureFiles() {

    // outputs a map of the file textures
    map<string, sf::Texture> textureMap;
    string files[20] = {"debug","digits","face_happy","face_lose","face_win","flag","mine","number_1","number_2",
                      "number_3", "number_4", "number_5", "number_6", "number_7", "number_8", "test_1",
                      "test_2", "test_3", "tile_hidden", "tile_revealed"};
    for(unsigned int i = 0; i < 20; i++)
    {
        sf::Texture texture;
        texture.loadFromFile("images/" + files[i] + ".png");
        textureMap.emplace(files[i], texture);
    }
    // Return the map of those textures.
    return textureMap;
}