#include "hit.hpp"
#include "shape.hpp"
#include <cmath>
#include <memory>
Hit::Hit():
m_hit{false},
m_distance{INFINITY},
m_intersect{INFINITY},
m_norm{INFINITY},
m_shape_ptr{nullptr}
{}
Hit::Hit(bool hit, float distance, glm::vec3 const& intersect,glm::vec3 const& norm, Shape* shape_ptr):
m_hit{hit},
m_distance{distance},
m_intersect{intersect},
m_norm{norm},
m_shape_ptr{shape_ptr}
{}