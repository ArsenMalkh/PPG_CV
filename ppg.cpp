
#include "bitmap/bitmap_image.hpp"
#include "ppg.h"
 
 
int PPG::hue_transit(int L1, int L2, int L3, int V1, int V3) {
    int V2;
    if (L1 < L2 && L2 < L3 || L1 > L2 && L2 > L3) {
        V2 = V1 + (V3 - V1) * (L2 - L1) / (L3 - L1);
    } else {
        V2 = (V1 + V3) / 2 + (L2 - (L1 + L3) / 2) / 2;
    }
    return V2; 
}

void PPG::get_G_on_RB(rgb_t* data, bool red_in_center) {
    if (red_in_center) {

        /*
            R0   G1   R2   G3   R4
            G5   B6   G7   B8   G9
            R10  G11  R12  G13  R14
            G15  B16  G17  B18  G19
            R20  G21  R22  G23  R24
        */
        
        uint dN = abs(data[12].red - data[ 2].red)*2 + abs(data[17].green - data[ 7].green);
        uint dE = abs(data[12].red - data[14].red)*2 + abs(data[11].green - data[13].green);
        uint dW = abs(data[12].red - data[10].red)*2 + abs(data[13].green - data[11].green);
        uint dS = abs(data[12].red - data[22].red)*2 + abs(data[ 7].green - data[17].green);

        uint dMin = std::min({dN, dE, dW, dS});

        if (dN == dMin) {
            data[12].green = (data[ 7].green * 3 + data[17].green + data[12].red - data[ 2].red)/4;
            return;
        }
        if (dE == dMin) {
            data[12].green = (data[13].green * 3 + data[11].green + data[12].red - data[14].red)/4;
            return;
        } 
        if (dW == dMin) {
            data[12].green = (data[11].green * 3 + data[13].green + data[12].red - data[10].red)/4;
            return;
        }

        data[12].green = (data[17].green * 3 + data[ 7].green + data[12].red - data[22].red)/4;

    } else {

        int dN = abs(data[12].blue - data[ 2].blue)*2 + abs(data[17].green - data[ 7].green);
        int dE = abs(data[12].blue - data[14].blue)*2 + abs(data[11].green - data[13].green);
        int dW = abs(data[12].blue - data[10].blue)*2 + abs(data[13].green - data[11].green);
        int dS = abs(data[12].blue - data[22].blue)*2 + abs(data[ 7].green - data[17].green);

        int32_t dMin = std::min({dN, dE, dW, dS});

        if (dN == dMin) {
            data[12].green = (data[ 7].green * 3 + data[17].green + data[12].blue - data[ 2].blue)/4;
            return;
        } 
        if (dE == dMin) {
            data[12].green = (data[13].green * 3 + data[11].green + data[12].blue - data[14].blue)/4;
            return;
        } 
        if (dW == dMin) {
            data[12].green = (data[11].green * 3 + data[13].green + data[12].blue - data[10].blue)/4;
            return;
        } 
            data[12].green = (data[17].green * 3 + data[ 7].green + data[12].blue - data[22].blue)/4;
    }
}
////////////////////////////////////////////////////////////////////
void PPG::get_RB_on_G(rgb_t* data, bool even_row) {
    if (even_row) {
        
        /*
            G0 R1 G2
            B3 G4 B5
            G6 R7 G8
        */

        data[4].blue = hue_transit( data[3].green, data[4].green, data[5].green, data[3].blue, data[5].blue);
        data[4].red = hue_transit( data[1].green, data[4].green, data[7].green, data[1].red, data[7].red);

    } else {

        data[4].red = hue_transit( data[3].green, data[4].green, data[5].green, data[3].red, data[5].red);
        data[4].blue = hue_transit( data[1].green, data[4].green, data[7].green, data[1].blue, data[7].blue);
    }
}
//////////////////////////////////////////////////////////////////////////////
void PPG::get_B_on_R_or_R_on_B(rgb_t* data, bool red_in_center) {
    if (red_in_center) {

        int dNE = abs(data[8].blue - data[16].blue) + abs(data[4].red - data[12].red) + abs(data[12].red - data[20].red) 
                    + abs(data[8].green - data[12].green) + abs(data[12].green - data[16].green);
        int dNW = abs(data[6].blue - data[18].blue) + abs(data[0].red - data[12].red) + abs(data[12].red - data[24].red)
            + abs(data[6].green - data[12].green) + abs(data[12].green - data[18].green);

        if (dNE < dNW) {
            data[12].blue = hue_transit( data[8].green, data[12].green, data[16].green, data[8].blue, data[16].blue);
            return;
        }

        data[12].blue = hue_transit( data[6].green, data[12].green, data[18].green, data[6].blue, data[18].blue);
    
    } else {
        
        int dNE = abs(data[8].red - data[16].red) + abs(data[4].blue - data[12].blue) + abs(data[12].blue - data[20].blue)
                    + abs(data[8].green - data[12].green) + abs(data[12].green - data[16].green);
        int dNW = abs(data[6].red - data[18].red) + abs(data[0].blue - data[12].blue) + abs(data[12].blue - data[24].blue)
                    + abs(data[6].green - data[12].green) + abs(data[12].green - data[18].green);

        if (dNE < dNW) { 
            data[12].red = hue_transit( data[8].green, data[12].green, data[16].green, data[8].red, data[16].red);
        } else {
            data[12].red = hue_transit( data[6].green, data[12].green, data[18].green, data[6].red, data[18].red);
        }
    }
}