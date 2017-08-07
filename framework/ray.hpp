#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>

struct Ray
{
    glm::vec3 origin;
    glm::vec3 direction;

    Ray():
    origin{glm::vec3{0.0}},
    direction{glm::vec3{1.0}}
    {}

    Ray(glm::vec3 origin, glm::vec3 direction):
    origin{origin},
    direction{direction}
    {}


};

#endif