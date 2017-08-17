#include "camera.hpp"
//Defualt
Camera::Camera():
  m_name {"Default Camera"},
  m_fov {75},
  m_pos {0, 0, 0},
  m_dir {-1, 0, 0},
  m_up {0, 0, -1}
  {}

Camera::Camera(std::string const& m_name,int const& m_fov, glm::vec3 const& m_pos, glm::vec3 const& m_dir, glm::vec3 const& m_up):
  m_name (m_name),
  m_fov (m_fov),
  m_pos (m_pos),
  m_dir (m_dir),
  m_up (m_up)
  {}
Camera::~Camera(){}

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

void Camera::print() 
{
        std::cout<<"\nname:"<<m_name<<"\n";
        std::cout<<"fov:"<<m_fov<<"\n";
        std::cout<<"pos:"<<m_pos.x<<" "<<m_pos.y<<" "<<m_pos.z<<"\n";
        std::cout<<"dir:"<<m_dir.x<<" "<<m_dir.y<<" "<<m_dir.z<<"\n";
        std::cout<<"upvec:"<<m_up.x<<" "<<m_up.y<<" "<<m_up.z<<"\n";
}
glm::mat4 Camera::CamTrans() const
{
  //m_pos=eye
  //m_up hat man schon
  glm::vec3 n = glm::normalize(m_dir);
  //normalizierte crossprducten
  glm::vec3 u = glm::normalize(glm::cross(n, m_up));
  glm::vec3 v = glm::normalize(glm::cross(u, n));

  glm::mat4 CamTrans;
  //4x4matrix
  CamTrans[0] = glm::vec4 {u, 0.0}; 
  CamTrans[1] = glm::vec4 {v, 0.0};
  CamTrans[2] = glm::vec4 {-1.0f*n, 0.0};
  CamTrans[3] = glm::vec4 {m_pos, 1.0};

  return CamTrans; 
} 
Ray const Camera::castray(glm::vec3 const& dir) const
{
  Ray ray{{0.0f,0.0f,0.0f}, m_dir};
  ray.transformRay(CamTrans());
  return ray;
}
