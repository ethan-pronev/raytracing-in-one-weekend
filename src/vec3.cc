#include <iostream>
#include <math.h>

#include "rtweekend.h"
#include "vec3.h"

using std::sqrt;


// vec3 Methods

double vec3::x() const { return e[0]; }
double vec3::y() const { return e[1]; }
double vec3::z() const { return e[2]; }

vec3 vec3::operator-() const { return vec3(-e[0], -e[1], -e[2]); }
double vec3::operator[](int i) const { return e[i]; }
double& vec3::operator[](int i) { return e[i]; }

vec3& vec3::operator+=(const vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

vec3& vec3::operator*=(const double t) {
    e[0] *=t;
    e[1] *=t;
    e[2] *=t;
    return *this;
}

vec3& vec3::operator/=(const double t) {
    return *this *= 1/t;
}

double vec3::length() const {
    return sqrt(length_squared());
}

double vec3::length_squared() const {
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}

bool vec3::near_zero() const {
    // Return true if the vector is close to zero in all dimentions
    const auto s = 1e-8;
    return (fabs(e[0]) < s && fabs(e[1]) < s && fabs(e[2]) < s);
}


// vec3 Utility Functions

vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1, 1);
        if (p.length() >=1) continue;
        return p;
    }
}

vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 reflect(const vec3 &v, const vec3 &n) {
    return v - 2*dot(v,n)*n;
}

vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat) {
    auto cos_thata = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_thata*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}
