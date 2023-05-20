#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <contrib/stb/stb_image.h>

Image::~Image()
{ 
    if ( _imgData ) 
        stbi_image_free(_imgData); 
}

void Image::load(const char* filename, int &width, int &height, int &nrComponents, int channel ) {
    _imgData = stbi_load(filename, &width, &height, &nrComponents, channel);
}