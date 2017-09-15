#ifndef AABB_HPP
#define AABB_HPP
#include <glm/glm.hpp>
#include "ray.hpp"
class AABB
{
private:
  glm::vec3 m_min;
  glm::vec3 m_max;
public:
  	AABB (); // default constructor
	AABB(glm::vec3 const& min,glm::vec3 const& max); //user
	~AABB(); //destructor


	glm::vec3 const& get_min() const;
	glm::vec3 const& get_max() const;
};
  #endif