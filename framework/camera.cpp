#include "camera.hpp"
//Defualt
Camera::Camera():
  m_name {"Default Camera"},
  m_fov {75},
  m_pos {0, 0, 0},
  m_dir {0, 0, -1},
  m_up {0, 1, 0}
  {
  glm::vec3 n = glm::normalize(m_dir);
  glm::vec3 u = glm::normalize(glm::cross(n, m_up));
  glm::vec3 v = glm::normalize(glm::cross(u, n));
  //4x4matrix
  m_worldtrans[0] = glm::vec4 {u, 0.0}; 
  m_worldtrans[1] = glm::vec4 {v, 0.0};
  m_worldtrans[2] = glm::vec4 {-1.0f*n, 0.0};
  m_worldtrans[3] = glm::vec4 {m_pos, 1.0};
  }
Camera::Camera(std::string const& name,int const& fov):
  m_name (name),
  m_fov (fov),
  m_pos {0,0,fov},
  m_dir {0,0,-1},
  m_up {0,1,0}
  {
  glm::vec3 n = glm::normalize(m_dir);
  glm::vec3 u = glm::normalize(glm::cross(n, m_up));
  glm::vec3 v = glm::normalize(glm::cross(u, n));
  //4x4matrix
  m_worldtrans[0] = glm::vec4 {u, 0.0}; 
  m_worldtrans[1] = glm::vec4 {v, 0.0};
  m_worldtrans[2] = glm::vec4 {-1.0f*n, 0.0};
  m_worldtrans[3] = glm::vec4 {m_pos, 1.0};

  }
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
Ray Camera::castray(float pixel_x, float pixel_y, float x_reso, float y_reso) const {

    glm::vec3 direction{pixel_x  / x_reso,pixel_y / y_reso, -1.0f * (0.5f / tan(m_fov/2.0f*M_PI/360.0f))}; 
  
    Ray camRay{m_pos, direction};

    return camRay.transformRay(m_worldtrans);
}


void Camera::CamRotate(float angle,glm::vec3 axis)
{
  angle=angle*M_PI/360;
  //https://math.stackexchange.com/questions/134741/a-4x4-homogeneous-matrix-for-a-90-degree-rotation-about-y-axis
  glm::mat4 CamRotate;
  if (axis.x!=0)
  {
  CamRotate[0] = glm::vec4 {1.0, 0.0,0.0,0.0};
  CamRotate[1] = glm::vec4 {0, cos(angle),sin(angle),0.0};
  CamRotate[2] = glm::vec4 {0, -sin(angle),cos(angle),0.0};
  CamRotate[3] = glm::vec4 {0.0, 0.0,0.0,1.0};
  m_worldtrans=m_worldtrans*CamRotate;
  }
  if (axis.y!=0)
  {
  CamRotate[0] = glm::vec4 {cos(angle), 0.0, -sin(angle), 0.0};
  CamRotate[1] = glm::vec4 {0.0, 1.0, 0.0, 0.0};
  CamRotate[2] = glm::vec4 {sin(angle), 0.0, cos(angle), 0.0};
  CamRotate[3] = glm::vec4 {0.0, 0.0, 0.0, 1.0};
  m_worldtrans=m_worldtrans*CamRotate;
  }
  if (axis.z!=0)
  {
  CamRotate[0] = glm::vec4 {cos(angle), sin(angle), 0.0, 0.0};
  CamRotate[1] = glm::vec4 {-sin(angle), cos(angle), 0.0, 0.0};
  CamRotate[2] = glm::vec4 {0.0, 0.0, 1.0, 0.0};
  CamRotate[3] = glm::vec4 {0.0, 0.0, 0.0, 1.0};  
  m_worldtrans=m_worldtrans*CamRotate;
  }

}

void Camera::CamTranslate(glm::vec3 offset)
{
glm::mat4 CamTranslate;
CamTranslate[0] = glm::vec4 {1.0f,0.0f,0.0f,0.0f};
CamTranslate[1] = glm::vec4 {0.0f,1.0f,0.0f,0.0f};
CamTranslate[2] = glm::vec4 {0.0f,0.0f,1.0f,0.0f};
CamTranslate[3] = glm::vec4 {offset.x,offset.y,offset.z,1.0f};
m_worldtrans=m_worldtrans*CamTranslate;
}

void Camera::CamScale(float value)
{
glm::mat4 CamScale;  
CamScale[0] = glm::vec4 {value,0.0f,0.0f,0.0f};
CamScale[1] = glm::vec4 {0.0f,value,0.0f,0.0f};
CamScale[2] = glm::vec4 {0.0f,0.0f,value,0.0f};
CamScale[3] = glm::vec4 {0.0f,0.0f,0.0f,1.0f};
m_worldtrans=m_worldtrans*CamScale;
}