#pragma once
#include "common.h"

struct hit_record;

// A material is an abstract interface to allow us to let different
// hittables render with different material types, wiht the
// behavior encapsulated in the interface, rather than having each
// hittable consist of all flags of each material type, setting
// only the ones for their own material type
class material {
public:
    virtual bool scatter(
        const ray& ray_in, const hit_record& hr, 
        color& attenuation, ray& scatt) const = 0;
};

// Lambertian reflectance is a type of diffusion
// for matte materials, below is its material defn.
class lambertian : public material {
public:
    lambertian(const color& a): albedo(a) {}

    virtual bool scatter(
        const ray& ray_in, const hit_record& hr, 
        color& attenuation, ray& scatt) const override {
            auto scatter_dir = hr.normal + random_unit_vector();

            // we need to ensure we don't generate random unit vec
            // exactly opposite of normal, will end up with NaNs
            // or other bad behavior later
            if (scatter_dir.near_zero()) {
                scatter_dir = hr.normal;
            }
            scatt = ray(hr.hit_point, scatter_dir);
            attenuation = albedo;
            return true;
        }
    
    color albedo;
};

// metal reflectance material
class metal : public material {
public:
    metal(const color& a, double f): albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(
        const ray& ray_in, const hit_record& hr, 
        color& attenuation, ray& scatt) const override {
            vec3 reflec = reflect(unit_vec(ray_in.direction()), hr.normal);
            scatt = ray(hr.hit_point, reflec + fuzz * rand_in_unit_sphere());
            attenuation = albedo;
            return dot(scatt.direction(), hr.normal) > 0;
        }
    
    color albedo;

    // Used for fuzzy reflection, get vector in unit sphere of 
    // reflection (range of +/- fizz for each part of hit point)
    double fuzz;
};


// dielectric reflectance material (glass-like)
class dielectric : public material {
public:
    dielectric(double idx_refraction): ir(idx_refraction) {}

    virtual bool scatter(
        const ray& ray_in, const hit_record& hr, 
        color& attenuation, ray& scatt) const override {
            attenuation = make_color(1.0, 1.0, 1.0);
            double refrac_ratio = hr.front_face ? (1.0 / ir) : ir;

            vec3 refraction = refract(unit_vec(ray_in.direction()), hr.normal, refrac_ratio);
            scatt = ray(hr.hit_point, refraction);
            return true;
        }

    double ir;
};


