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