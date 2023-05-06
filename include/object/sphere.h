#pragma once

#include "hittable.h"
#include "rtweekend.h"

class sphere: public hittable {
  private:
    point3 center;
    double radius;
    shared_ptr<material> mat_ptr;

  public:
    sphere() {}
    sphere(point3 cen, double r, shared_ptr<material> m): center{cen}, radius{r}, mat_ptr{m} {}

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
};
