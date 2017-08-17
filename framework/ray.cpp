#include "ray.hpp"
    Ray::Ray():
    m_origin{glm::vec3{0,0,0}},
    m_direction{glm::vec3{0,0,0}},
    m_inverse{glm::vec3{-0,-0,-0}}
    {}

    Ray::Ray(glm::vec3 origin, glm::vec3 direction,glm::vec3 inverse):
    m_origin{origin},
    m_direction{direction},
    m_inverse{inverse}
    {}
	Ray Ray::transformRay(glm::mat4 const& mat)
	{
	  glm::vec4 temp_org {m_origin, 1.0f};
	  glm::vec4 temp_dir {m_direction, 0.0f};
	  glm::vec3 temp2_org {mat * temp_org };
	  glm::vec3 temp2_dir {mat * temp_dir};
	  m_origin = temp2_org;
	  m_direction = glm::normalize(temp2_dir);
	  return *this;
	}