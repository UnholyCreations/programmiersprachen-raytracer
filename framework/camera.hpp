#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <string>
#include <iostream>
#include <ostream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
//#include <glm/mat4.hpp>
#include "ray.hpp"
class Camera
{
public:
	Camera(); //Default
	Camera(std::string const& name,int const& fov); //User
	~Camera(); //Destructor

	//Getters
	std::string const& get_name() const;
	int const& get_fov() const;
	glm::vec3 const& get_pos() const;
	glm::vec3 const& get_dir() const;
	glm::vec3 const& get_upvec() const;	
	Ray castray(float pixel_x, float pixel_y, float x_reso, float y_reso) const;

	//setter
	void CamRotate(float angle,glm::vec3 axis);
	void CamTranslate(glm::vec3 offset);
	//print
	void print();
	//DATA

  	std::string m_name;
  	int m_fov;
  	glm::vec3 m_pos; 
  	glm::vec3 m_dir; 
  	glm::vec3 m_up; 
  	glm::mat4 m_worldtrans;
};



#endif