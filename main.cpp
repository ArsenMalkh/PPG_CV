#include <iostream>
#include "bitmap/bitmap_image.hpp"
#include "restorer.h"
#include <chrono>

using namespace std;

int main(int argc, char** argv) {
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    if(argc != 3) {
        cout<<"Arguments are invalide"<<"\n";
        return 0;
    }

    char* input_image = argv[1];
    char* output_image = argv[2];
    
    bitmap_image image(input_image);

    Restorer s;
    // get start time
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    
    bitmap_image image2 = s.add_padding(image);
    s.Interpolate(image2);
    image = s.delete_padding(image2); 
    // get End time
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();

    int duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    cout << "Time duration = " << duration <<"ms"<< "\n"; 
    image.save_image(output_image);

    return 0;
}