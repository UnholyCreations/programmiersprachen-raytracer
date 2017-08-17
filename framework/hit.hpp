#ifndef HIT_HPP
#define HIT_HPP
#include <glm/vec3.hpp>
#include <memory>
#include "ray.hpp"
#include "shape.hpp"
#include "hit.hpp"
class Shape; //Shape not declared? :D


struct Hit
{
Hit();
Hit(bool hit, float dist, glm::vec3 const& intersect,glm::vec3 const& norm, Shape* shape_ptr);
bool m_hit;
float m_dist;
glm::vec3 m_intersect;
glm::vec3 m_norm;
Shape* m_shape_ptr;
};


#endif 