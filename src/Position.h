#pragma once 

#include <glm/vec2.hpp>
#include <anax/anax.hpp>

struct Position : anax::Component {
    Position(glm::vec2 position) : vec(position) {};
    Position(float x, float y) : vec(x, y) {};

    glm::vec2 vec;
};
