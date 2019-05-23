//
// Created by kieran on 23/05/19.
//

#include <iostream>
#include "texture.h"
#include "util/bitmap.h"

void texture::open(std::string const &filename)
{
    BITMAPINFO *info;

    rgbData = LoadDIBitmap((char *) filename.c_str(), &info);
    if (rgbData == nullptr)
    {
        std::cerr << "Error loading image: " << " " << filename << std::endl;
        exit(1);
    }

    height = info->bmiHeader.biHeight;
    width = info->bmiHeader.biWidth;

    printf("\nLoaded a %d by %d texture\n\n", height, width);
}