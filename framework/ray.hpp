#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>
//include <glm/vec3.hpp>

struct Ray
{
    glm::vec3 m_origin;
    glm::vec3 m_direction;
    glm::vec3 m_inverse;
    Ray();
    Ray(glm::vec3 origin, glm::vec3 direction,glm::vec3 inverse);

    glm::vec3 getorigin() const {
	return m_origin;
	}
    Ray transformRay(glm::mat4 const& mat);

};

#endif