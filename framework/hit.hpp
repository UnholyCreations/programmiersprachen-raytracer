#ifndef HIT_HPP
#define HIT_HPP
#include <glm/vec3.hpp>
#include <memory>
#include "ray.hpp"
#include "shape.hpp"
struct Hit
{
Hit();
Hit(bool hit, float dist, glm::vec3 const& target,glm::vec3 const& norm, Shape* shape_ptr);
bool m_hit;
float m_dist;
glm::vec3 m_target;
glm::vec3 m_norm;
Shape* m_shape_ptr;
};


#endif 