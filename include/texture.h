//
// Created by kieran on 23/05/19.
//

#ifndef CITS3003_TEXTURE_H
#define CITS3003_TEXTURE_H

#include <string>

struct texture
{
    int width;
    int height;
    unsigned char *rgbData;   // Array of bytes with the colour data for the texture
    unsigned int id;

    static texture openFromFile(std::string const &filename);
};

#endif //CITS3003_TEXTURE_H
