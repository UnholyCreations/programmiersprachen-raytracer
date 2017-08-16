#include "hit.hpp"
#include "shape.hpp"
#include <cmath>

Hit::Hit():
m_hit{false},
m_dist{INFINITY},
m_target{INFINITY},
m_norm{INFINITY},
m_shape_ptr{nullptr}
{}
Hit::Hit(bool hit, float dist, glm::vec3 const& target,glm::vec3 const& norm, Shape* shape_ptr):
m_hit{hit},
m_dist{dist},
m_target{target},
m_norm{norm},
m_shape_ptr{shape_ptr}
{}