#include "Wall.hpp"

#include "../Scene.hpp"
#include "../Load.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
// from https://stackoverflow.com/questions/11515469/how-do-i-print-vector-values-of-type-glmvec3-that-have-been-passed-by-referenc
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include <iostream>

// called by Mode, should be in update function
void Wall::update_position(float elapsed) {
    return GameObject::update_position(elapsed);
} 

// called by Mode, should be in update function
void Wall::update_rotation(float elapsed) {
    return GameObject::update_rotation(elapsed);
} 