//
// Created by kieran on 23/05/19.
//

#include <iostream>
#include <GL/glew.h>
#include "texture.h"
#include "util/bitmap.h"

texture texture::openFromFile(std::string const &filename)
{
    texture t{};

    BITMAPINFO *info;

    t.rgbData = LoadDIBitmap((char *) filename.c_str(), &info);
    if (t.rgbData == nullptr)
    {
        std::cerr << "Error loading image: " << " " << filename << std::endl;
        exit(1);
    }

    t.height = info->bmiHeader.biHeight;
    t.width = info->bmiHeader.biWidth;

    std::cout << "\nLoaded a " << t.height << " by " << t.width << " texture\n" << std::endl;

    glGenTextures(1, &t.id);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, t.id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t.width, t.height, 0, GL_RGB, GL_UNSIGNED_BYTE, t.rgbData);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    return t;
}