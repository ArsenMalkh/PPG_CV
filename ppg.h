#pragma once

#include "bitmap/bitmap_image.hpp"


class PPG {
private:
    static int hue_transit(int L1, int L2, int L3, int V1, int V3);

public:
    static void get_G_on_RB(rgb_t* data, bool red_in_center); //first stage
    static void get_RB_on_G(rgb_t* data, bool even_row); // second stage
    static void get_B_on_R_or_R_on_B(rgb_t* data, bool red_in_center); // third stage
};