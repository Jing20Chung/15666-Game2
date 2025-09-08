#include "Floor.hpp"

#include "../Scene.hpp"
#include "../Load.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
// from https://stackoverflow.com/questions/11515469/how-do-i-print-vector-values-of-type-glmvec3-that-have-been-passed-by-referenc
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include <iostream>

void Floor::init() {
    tag = "Floor";
}
