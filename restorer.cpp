#include <iostream>
#include "bitmap/bitmap_image.hpp"
#include "block.hpp"
#include "ppg.h"
#include "restorer.h"



void Restorer::Interpolate(bitmap_image& image) {
    
    height_ = image.height();
    width_ = image.width();

    this->iterate_RB(image);
    this->iterate_G(image);
    this->iterate_R_G(image);

}
///////////////////////////////////////////////////////////////////
bitmap_image Restorer::add_padding(bitmap_image& image) {
    height_ = image.height();
    width_ = image.width();

    bitmap_image image2(width_ + 4, height_ + 4);
    rgb_t colour;

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
                
                image.get_pixel(x, y, colour);
                image2.set_pixel(x + 2, y + 2, colour);
        }
    }
    for(int x = 0; x < 2; ++x) {
        for(int y = 0; y < height_; ++y) {
            image.get_pixel(x, y, colour);
            image2.set_pixel(x, y, colour);
        }
    }
    for(int x = width_+ 2; x < width_ + 4; ++x) {
        for(int y = 0; y < height_; ++y) {
            image.get_pixel(x - 4, y, colour);
            image2.set_pixel(x, y, colour);
        }
    }
    for(int y = 0; y < 2; ++y) {
        for(int x = 0; x < height_ + 4; ++x) {
            image2.get_pixel(x, y + 2, colour);
            image2.set_pixel(x, y, colour);
        }
    }
    for(int y = height_+ 2; y < height_ + 4; ++y) {
        for(int x = 0; x < height_ + 4; ++x) {
            image2.get_pixel(x, y - 2, colour);
            image2.set_pixel(x, y, colour);
        }
    }
    return image2;  
}
////////////////////////////////////////////////////////////////
bitmap_image Restorer::delete_padding(bitmap_image& image) {
    bitmap_image image2(width_ - 4, height_ - 4);
    rgb_t colour; 

    for(int y = 2; y < height_ - 2; ++y) {
        for(int x = 2; x < width_ - 2; ++x) {
            image.get_pixel(x, y, colour);
            image2.set_pixel(x - 2, y - 2, colour);
        }
    }
    return image2;
}
/////////////////////////////////////////////////////////////////
// когда мы знаем либо R либо B и хотим найти G
void Restorer::iterate_RB(bitmap_image& image) {

    Blocks block(5);

    for (int y = 0; y + block.getSize() <= height_; ++y) {
        for (int x = y % 2; x + block.getSize() <= width_; x += 2) {
            block.read(image, x, y);
            PPG::get_G_on_RB(block.getData(), !(y % 2));
            block.write(image, x, y);
        }
    }
}
// когда мы знаем G и хотим найти R и B
void Restorer::iterate_G(bitmap_image& image) {
    Blocks block(3);

    for (int y = 0; y + block.getSize() <= height_; ++y) {
        for (int x = (y+1) % 2; x + block.getSize() <= width_; x += 2) {
            block.read(image, x, y);
            PPG::get_RB_on_G(block.getData(), !(y % 2));
            block.write(image, x, y);
        }
    }
}
// когда мы знаем R и незнaем B либо знаем B но незнаем А.
void Restorer::iterate_R_G(bitmap_image& image) {
    
    Blocks block(5);

    for (int y = 0; y + block.getSize() <= height_; ++y) {
        for (int x = y % 2; x + block.getSize() <= width_; x += 2) {
            block.read(image, x, y);
            PPG::get_B_on_R_or_R_on_B(block.getData(), !(y % 2));
            block.write(image, x, y);
        }
    }
}
