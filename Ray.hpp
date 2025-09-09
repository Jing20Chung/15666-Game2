#pragma once
#include <glm/glm.hpp>
#include "GameObjects/GameObject.hpp"

// Reference: https://github.com/CMU-Graphics/Scotty3D/blob/main/assignments/A3/T3-bounding-volume-hierarchy.md
// Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection.html
struct Ray {
    Ray(){}
    ~Ray(){}
    Ray(const glm::vec3 origin_, const glm::vec3 direction): origin(origin_), dir(direction) {
        inv_dir = 1.0f / dir;
    }

    glm::vec3 origin;
    glm::vec3 dir;
    glm::vec3 inv_dir;

    bool hit(const Bounds& bbox, glm::vec2& time);
};