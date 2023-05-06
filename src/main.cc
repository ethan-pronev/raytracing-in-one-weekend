#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "scenes.h"
#include "sphere.h"

#include <iostream>

using std::cout;
using std::cerr;
using std::flush;

color ray_color(const ray &r, const hittable &world, int depth) {
    if (depth <= 0) return color(0,0,0); // return black when bounce limit reached

    // find any object that this ray hits and color it according to surface normal
    hit_record rec;
    if (world.hit(r, 0.001, infinity, rec)) { // use 0.001 to fix shadow acne
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth-1);
        }
        return color(0,0,0);
    }

    // if no objects are hit, color sky with blue/white gradient
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {
    // Image

    const auto aspect_ratio = 3.0 / 2.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 50;
    const int max_depth = 50;

    // World & Camera

    hittable_list world;
    camera cam;
    scene1(world, cam, aspect_ratio);

    // Render

    cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; j--) {
        cerr << "\rProgress: " << (image_height-1-j)*100/(image_height-1) << "% (" << j << " lines remaining)" << flush;
        for (int i = 0; i < image_width; i++) {
            color pixel_color(0, 0, 0);
            for (int s=0; s<samples_per_pixel; s++) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    cerr << "\nDone.\n";
}
