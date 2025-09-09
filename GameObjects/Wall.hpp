#pragma once

#include "GameObject.hpp"
#include "../Load.hpp"

struct Wall : GameObject{
    virtual void init() override;
};
