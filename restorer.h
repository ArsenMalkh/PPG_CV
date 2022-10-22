#pragma once

#include <iostream>
#include "bitmap/bitmap_image.hpp"
#include "block.hpp"
#include "ppg.h"

class Restorer {
private:
    int height_;
    int width_;
public:
    void Interpolate(bitmap_image& image);
    bitmap_image add_padding(bitmap_image& image);
    bitmap_image delete_padding(bitmap_image& image);
private:
    // когда мы знаем либо R либо B и хотим найти G
    void iterate_RB(bitmap_image& image);
    // когда мы знаем G и хотим найти R и B
    void iterate_G(bitmap_image& image);
    // когда мы знаем R и незнaем B либо знаем B но незнаем А.
    void iterate_R_G(bitmap_image& image);
};