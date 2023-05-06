#pragma once

#include "rtweekend.h"
#include "hittable.h"


class material {
  public:
    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const = 0;
};


class lambertian: public material {
  private:
    color albedo;

  public:
    constexpr lambertian(const color &a): albedo{a} {}

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override;
};


class metal: public material {
  private:
    color albedo;
    double fuzz;

  public:
    constexpr metal(const color &a, double f): albedo{a}, fuzz{f < 1 ? f : 1} {}

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override;
};


class dielectric: public material {
  private:
    color albedo; // TODO: see if there is a better way to do glass tint
    double ir; // Index of Refraction

  public:
    constexpr dielectric(double index_of_refraction): albedo{color(1.0, 1.0, 1.0)}, ir{index_of_refraction} {}
    constexpr dielectric(const color &a, double index_of_refraction): albedo{a}, ir{index_of_refraction} {}

    virtual bool scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const override;

  private:
    static double reflectance(double cosine, double ref_idx) {
        // Use Shlick's approximation for reflectance
        auto r0 = (1-ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }
};
