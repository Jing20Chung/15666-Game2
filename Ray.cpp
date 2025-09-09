#include "Ray.hpp"

// Reference: https://github.com/CMU-Graphics/Scotty3D/blob/main/assignments/A3/T3-bounding-volume-hierarchy.md
// This code is adapted from my Spring 2025 CG A3T3 assignment
bool Ray::hit(const Bounds& bbox, glm::vec2& time) {
    glm::vec3 max = bbox.max;
    glm::vec3 min = bbox.min;
    float tmin, tmax, t0y, t1y, t0z, t1z;
    if (inv_dir.x >= 0) {
        tmin = (min.x - origin.x) * inv_dir.x;
        tmax = (max.x - origin.x) * inv_dir.x;
    }
    else {
        tmax = (min.x - origin.x) * inv_dir.x;
        tmin = (max.x - origin.x) * inv_dir.x;
    }

    if (inv_dir.y >= 0) {
        t0y = (min.y - origin.y) * inv_dir.y;
        t1y = (max.y - origin.y) * inv_dir.y;
    }
    else {
        t1y = (min.y - origin.y) * inv_dir.y;
        t0y = (max.y - origin.y) * inv_dir.y;
    }

    if (t1y < tmin || tmax < t0y) return false;

    if (t1y < tmax) tmax = t1y;
    if (t0y > tmin) tmin = t0y;

    if (inv_dir.z >= 0) {
        t0z = (min.z - origin.z) * inv_dir.z;
        t1z = (max.z - origin.z) * inv_dir.z;
    }
    else {
        t1z = (min.z - origin.z) * inv_dir.z;
        t0z = (max.z - origin.z) * inv_dir.z;
    }

    if (t0z > tmax || t1z < tmin) return false;

    if (t0z > tmin) tmin = t0z;
    if (t1z < tmax) tmax = t1z;
    
    time = glm::vec2(tmin, tmax);
    // if ( !(tmin >= times.x && tmin <= times.y) && !(tmax >= times.x && tmax <= times.y)) return false;

    // if (tmin >= times.x && tmin <= times.y) {
    //     times.x = std::max(times.x, tmin);
    // }
    // if (tmax >= times.x && tmax <= times.y) {
    //     times.y = std::min(times.y, tmax);
    // }
    return true;
}