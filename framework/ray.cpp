#include "ray.hpp"
    Ray::Ray():
    m_origin{glm::vec3{0,0,0}},
    m_direction{glm::vec3{-1,-1,-1}}
    {}

    Ray::Ray(glm::vec3 origin, glm::vec3 direction):
    m_origin{origin},
    m_direction{direction}
    {}
