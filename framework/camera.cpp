#include "camera.hpp"
//Defualt
Camera::Camera():
  m_name {"Default_Camera"},
  m_fov {75},
  m_pos {0, 0, 0},
  m_dir {-1, 0, 0},
  m_up {0, 0, -1}
  {std::cout<<"cam default\n";}

Camera::Camera(std::string const& m_name,int const& m_fov, glm::vec3 const& m_pos, glm::vec3 const& m_dir, glm::vec3 const& m_up):
  m_name (m_name),
  m_fov (m_fov),
  m_pos (m_pos),
  m_dir (m_dir),
  m_up (m_up)
  {std::cout<<"camera user\n";}
Camera::~Camera(){std::cout<<"camera dies\n";}

std::string const& Camera::get_name() const
{
  return m_name;
}
int const& Camera::get_fov() const{
  return m_fov;
}

glm::vec3 const& Camera::get_pos() const{
  return m_pos;
}

glm::vec3 const& Camera::get_dir() const{
  return m_dir;
}
glm::vec3 const& Camera::get_upvec() const{
  return m_up;
} 