#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <string>
#include <iostream>
#include <ostream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
class Camera
{
public:
	Camera(); //Default
	Camera(std::string const& name,int const& fov, glm::vec3 const& pos, glm::vec3 const& dir , glm::vec3 const& up); //User
	~Camera(); //Destructor

	//Getters
	std::string const& get_name() const;
	int const& get_fov() const;
	glm::vec3 const& get_pos() const;
	glm::vec3 const& get_dir() const;
	glm::vec3 const& get_upvec() const;	
	void print();
	//DATA

  	std::string m_name;
  	int m_fov;
  	glm::vec3 m_pos; 
  	glm::vec3 m_dir; 
  	glm::vec3 m_up; 
};



#endif