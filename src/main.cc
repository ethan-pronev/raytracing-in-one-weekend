#include "color.h"
#include "vec3.h"

#include <iostream>

using std::cout;
using std::cerr;
using std::flush;

int main() {
    const int w=256 ,h=256;
    cout << "P3\n" << w << " " << h << "\n255\n";
    for (int i=0; i<h; i++) {
        cerr << "\rProgress: " << i*100/(h-1) << "% (" << h-1-i << " lines remaining)" << flush;
        for (int j=0; j<w; j++) {
            color pixel_color(double(i)/(h-1), 0.25, double(j)/(w-1));
            write_color(std::cout, pixel_color);
        }
    }
    cerr << "\nDone.\n";
}