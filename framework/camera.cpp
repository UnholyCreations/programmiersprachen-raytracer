#include "camera.hpp"
//Defualt
Camera::Camera():
  m_name ({"Default_Camera"}),
  m_fov (75),
  m_pos ({0, 0, 0}),
  m_dir ({0, -1, 0}),
  m_up ({0, 0, 1})
  {}

Camera::Camera(std::string const& m_name, int m_fov, glm::vec3 const& m_pos, glm::vec3 const& m_dir, glm::vec3 const& m_up):
  m_name (m_name),
  m_fov (m_fov),
  m_pos (m_pos),
  m_dir (m_dir),
  m_up (m_up)
  {}
Camera::~Camera(){std::cout<<"camera dies";}