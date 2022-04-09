#pragma once
#include "common.h"
#include "hittable.h"

class hittable_list : public hittable {
public:
    hittable_list() {}
    hittable_list(shared_ptr<hittable> obj) {add(obj);}

    void clear() {objects.clear();}
    void add(shared_ptr<hittable> obj) {
        objects.push_back(obj);
    }
    
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
private:
    vector<shared_ptr<hittable>> objects;
};