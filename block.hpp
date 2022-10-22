#pragma once

#include "bitmap/bitmap_image.hpp"

class Blocks {
    private:
        int  size_;
        rgb_t* data_;
    public:
        Blocks(int size) : size_(size) {
            data_ = new rgb_t[size_*size_];
        }
        void read(const bitmap_image& image, int up_left_x, int up_left_y) { 

            for (size_t y = 0; y < size_; ++y) {
                for (size_t x = 0; x < size_; ++x) {
                    image.get_pixel(up_left_x + x, up_left_y + y, data_[y*size_ + x]);
                }
            }
        }
        void write(bitmap_image& image, int up_left_x, int up_left_y) { 

            for (size_t y = 0; y < size_; ++y) {
                for (size_t x = 0; x < size_; ++x) {
                    image.set_pixel(up_left_x + x, up_left_y + y, data_[y*size_ + x]);
                }
            }
        }
        rgb_t* getData() {
            return data_;
        }
        int  getSize() {
            return size_;
        }
};