#include "AABB.hpp"
AABB::AABB(): m_min{0,0,0},m_max{1,1,1} {}
AABB::AABB(glm::vec3 const& min,glm::vec3 const& max): m_max{min}, m_min{max} {}
AABB::~AABB() {}

glm::vec3 const& AABB::get_min() const
{

	return m_min;
}
glm::vec3 const& AABB::get_max() const
{

  return m_max;
}	
bool AABB::intersect(Ray const& ray)
{

if 
(
ray.m_origin.x>m_min.x &&
ray.m_origin.y>m_min.y &&
ray.m_origin.z>m_min.z &&
ray.m_origin.x>m_max.x &&
ray.m_origin.y>m_max.y &&
ray.m_origin.z>m_max.z 
) 
{
  return 1;
}


float tmin, tmax, tymin, tymax, tzmin, tzmax;
if (ray.m_direction.x >= 0) {
    tmin = (m_min.x - ray.m_origin.x) * ray.m_inverse.x;
    tmax = (m_max.x - ray.m_origin.x) * ray.m_inverse.x;
}
else {
    tmin = (m_max.x - ray.m_origin.x) * ray.m_inverse.x;
    tmax = (m_min.x - ray.m_origin.x) * ray.m_inverse.x;
}
if (ray.m_direction.y >= 0) {
    tymin = (m_min.y - ray.m_origin.y) * ray.m_inverse.y;
    tymax = (m_max.y - ray.m_origin.y) * ray.m_inverse.y;
} else {
    tymin = (m_max.y - ray.m_origin.y) * ray.m_inverse.y;
    tymax = (m_min.y - ray.m_origin.y) * ray.m_inverse.y;
}
if ((tmin > tymax) || (tymin > tmax)) {
    return 0;
}
if (tymin > tmin) {
    tmin = tymin;
}
if (tymax < tmax) {
    tmax = tymax;
}
if (ray.m_direction.z >= 0) {
    tzmin = (m_min.z - ray.m_origin.z) * ray.m_inverse.z;
    tzmax = (m_max.z - ray.m_origin.z) * ray.m_inverse.z;
} else {
    tzmin = (m_max.z - ray.m_origin.z) * ray.m_inverse.z;
    tzmax = (m_min.z - ray.m_origin.z) * ray.m_inverse.z;
}
if ((tmin > tzmax) || (tzmin > tmax)) {
    return 0;
}
if (tzmin > tmin) {
    tmin = tzmin;
}
if (tzmax < tmax) {
    tmax = tzmax;
}

if (tmax > std::max(tmin, 0.0f))
{
return 1;
}
else
{
return 0;
}
}