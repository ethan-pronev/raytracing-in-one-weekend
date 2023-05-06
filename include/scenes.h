#pragma once

#include "camera.h"
#include "hittable_list.h"


// Re-create simpe 3-sphere scene from first book
void scene0(hittable_list &world, camera &cam, double aspect_ratio);

// Recreate the final scene from the first book
void scene1(hittable_list &world, camera &cam, double aspect_ratio);
